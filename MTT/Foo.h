#pragma once

#include <string>
#include <fstream>
#include <mutex>

class Foo
{
private:
	std::ofstream *mFile;
	mutable std::mutex mLock;
public:
	Foo()
		:
		mFile(nullptr)
	{
		mFile = new std::ofstream("c:\\code\\blog.txt", std::ios_base::trunc | std::ios_base::out);
	}

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
		return (mFile != nullptr) && mFile->is_open();
	}

	template<typename OutputItem>
	void Output(const OutputItem& output)
	{
		if (Available())
		{
			std::scoped_lock lock(mLock);
			*mFile << output << "\r\n";
		}
	}

	template<typename OutputItem, typename ...Others>
	void Output(const OutputItem& output, Others... others)
	{
		if (Available())
		{
			std::scoped_lock lock(mLock);
			*mFile << output << "\r\n";
		}
		Output(others...);
	}

};
