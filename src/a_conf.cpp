#include "a_conf.h"

using namespace std;

char * app_path = NULL;

void SetAppPath(char p[])
{
	app_path = &p[0];
}

string GetAppPath()
{
	if (app_path == NULL)
		return "";
	return string(app_path);
}

string JoinPath(const string& root, const string& file)
{
	if ( root.find("\\") != string::npos ) {
		return root.substr( 0, root.rfind( "\\" ) ) + "\\" + file;
	} else if ( root.find("/") != string::npos) {
		return root.substr( 0, root.rfind( "/" ) ) + "/" + file;
	} else {
		return file;
	}
}

string FullPathTo(const string& file)
{
	if (app_path == NULL)
		return file;
	string s( app_path );
	if ( s.find("\\") != string::npos ) {
		return s.substr( 0, s.rfind( "\\" ) ) + "\\" + file;
	} else if ( s.find("/") != string::npos) {
		return s.substr( 0, s.rfind( "/" ) ) + "/" + file;
	} else {
		return file;
	}
}