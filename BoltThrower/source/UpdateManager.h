#ifndef UpdateManager_H_
#define UpdateManager_H_

#include "GCTypes.h"
//#include "HashLabel.h"
//#include "HashString.h"
#include <string>
//#include <map>
//#include <vector>

using namespace std;


class UpdateManager
{
public:
	UpdateManager();

	void Init();

	void DoUpdate();
	bool DisplayUpdateMessage();
	bool CheckForUpdate();
	void  UpdateApplicationFiles();

	void SetMessageVersionReport(string Value) { m_MessageVersionReport = Value; }
	string GetMessageVersionReport() const { return m_MessageVersionReport; }

	string m_ReleaseNotes;
	string m_LatestReleaseAvailable;


	vector<FileInfo> m_ApplicationSpecificUpdatesForDownloadFileInfoContainer;


private:

	string m_MessageVersionReport;
};

#endif
