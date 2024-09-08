#ifndef APP_H
#define APP_H
#define kAppSignature "application/x-vnd.Brightnesser"
#define kAppName "Brightness control"
#include <Application.h>

	
class App : public BApplication
{
public:
	App(void);
	virtual	void	AboutRequested();
};

#endif
