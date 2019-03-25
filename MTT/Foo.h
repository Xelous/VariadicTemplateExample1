#pragma once

#include <string>
#include <fstream>
#include <mutex>
#include <memory>
#include <utility>

namespace Xelous
{
	class Foo;
	using FooPtr = std::unique_ptr<Foo>;
	class Foo
	{
	private:
		std::ofstream* mFile;
		mutable std::mutex mLock;

		Foo(const std::string& pFilename)
			:
			mFile(nullptr)
		{
			mFile = new std::ofstream(pFilename.c_str(), std::ios_base::trunc | std::ios_base::out);
		}		

		static FooPtr sMasterInstance;

	public:

		static auto Create(const std::string& pFilename = "c:\\code\\blog.txt")
		{
			return FooPtr(
				new Foo(
					std::forward<const std::string&>(
						pFilename)));
		}

		static auto Get()
		{
			if (!sMasterInstance)
			{
				sMasterInstance = Create();
			}
			return sMasterInstance.get();
		}

		Foo() = delete;
		Foo(const Foo&) = delete;
		Foo(const Foo&&) = delete;
		void operator=(const Foo&) = delete;
		void operator=(const Foo&&) = delete;

		~Foo()
		{
			if (Available())
			{
				std::scoped_lock lock(mLock);
				mFile->close();
				delete mFile;
				mFile = nullptr;
			}
		}

		const bool Available() const
		{
			std::scoped_lock lock(mLock);
			return (mFile != nullptr) &&
				mFile->is_open() &&
				!mFile->bad();
		}

		template<typename OutputItem>
		void Output(const OutputItem & output)
		{
			if (Available())
			{
				std::scoped_lock lock(mLock);
				*mFile << output << "\r\n";
			}
		}

		template<typename OutputItem, typename ...Others>
		void Output(const OutputItem & output, Others... others)
		{
			if (Available())
			{
				std::scoped_lock lock(mLock);
				*mFile << output << "\r\n";
			}
			Output(others...);
		}

	};

	FooPtr Foo::sMasterInstance{ nullptr };
	


}