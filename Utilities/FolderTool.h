#pragma once
#include <string>

#pragma comment(lib, "comsuppw.lib")

namespace FileSystem
{
	class CCurrentDirectoryTempSwitcher
	{
	public:
		CCurrentDirectoryTempSwitcher(const TCHAR* directory);
		~CCurrentDirectoryTempSwitcher();
	protected:
		CString _last_current_directory;
	};

	/// Declare an instance of this class to enable fstream to open files with chinese characters in path.
	class CFileHelper
	{
	public:
		CFileHelper();
		~CFileHelper();

		CString _locale;
	};

	bool IsDirectoryEmpty(const CString& directory);
	bool DeleteMultiFile(const CString& directory, const CString& filename);
	bool DeleteDirectory(const CString& directory, bool bDeleteItself = true);
	bool CopyDirectory(const CString& source, const CString& destination, bool force_uppercase_dest_path = false);

	bool CreateFolder(const CString& folder);
	bool CreateFolderTree(const CString& path);
	long GetFolderSize(const CString& folder);	// 得到目录中所含文件的总容量

	bool FileExists(const CString& filename);
	bool IsFileReadonly(const CString& filepath);

	CString GetCurrentDirectory();

	CString GetFolderFromPath(const CString& file);
	CString GetFileNameFromPath(const CString& path);
	CString GetFileExtensionFromPath(const CString& path);

	int MyGetDiskFreeSpaceEx(LPCSTR pszDrive);
	bool IsValidPath(const CString& path);
	bool IsFolderEqual(const CString& dir1, const CString& dir2);

	CString FindFileInDirectory(const CString& directory_path, const CString& file_name, bool include_subdirectory = false);

	CString GetStartPath();

	CString GetTempFilePath(const CString& prefix);
#ifndef NO_BOOST
	CString SimplifyPath(const CString& path);
#endif
};

