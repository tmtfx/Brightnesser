#include "MainWindow.h"

#ifdef __HAIKU__
#	include <Alert.h>
#endif

#include "OutlineView.h"
#include "App.h"
#include <InterfaceDefs.h>
#include <View.h>
#include <stdlib.h>
#include <String.h>



const float kDraggerSize = 7;

OutlineView::OutlineView(BRect frame)
	:
	BView(frame, kAppName, B_FOLLOW_ALL, B_WILL_DRAW|B_PULSE_NEEDED),
	fSlider(NULL),fDragger(NULL)
{
	fReplicated = false;
	prevValue = 0;
	frame.left = frame.right - kDraggerSize;
	frame.top = frame.bottom - kDraggerSize;

	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	BRect r(15,15,Bounds().right - 15, Frame().bottom - 15);
	fMx = new BMessage(9731);
	fSlider = new BSlider(r, "brigth_slider","Brightness", fMx,1,10);
	fSlider->SetKeyIncrementValue(1);
	//fScreen = new BScreen();
	
	//BDragger *dragger = new BDragger(frame, this, B_FOLLOW_RIGHT | B_FOLLOW_BOTTOM);
	//AddChild(dragger);
	fDragger = new BDragger(frame, this, B_FOLLOW_RIGHT | B_FOLLOW_BOTTOM);
	AddChild(fDragger);
	AddChild(fSlider);
	float fValue;
	BScreen fScreen;
	status_t status = fScreen.GetBrightness(&fValue);
	
	if (status == B_OK)
		{
			int32 value = static_cast<int>(fValue * 10);//BSCreen GetBrightness
			if (value < 1) {
        		value = 1;
    		} else if (value > 10) {
        		value = 10;
   			}
    		fSlider->SetValue(value);
		}
		else	
		{
			int32 value = 10;
			fSlider->SetValue(value);
		}
	
}



void
OutlineView::Pulse(){
	//fScreen = new BScreen();
	BScreen fScreen;
	int32 value = fSlider->Value();
	if (prevValue!=value){
	float valore_float = static_cast<float>(value) / 10.0f;
	valore_float = std::max(0.1f, std::min(valore_float, 1.0f));
	status_t status = fScreen.SetBrightness(valore_float);
	prevValue=value;
	}
	if (!IsHidden()) {
			Draw(Bounds());
		}
}


OutlineView::OutlineView(BMessage *archive)
	:
	BView(archive)
{
	
	fReplicated = true;

	SetViewColor(B_TRANSPARENT_COLOR);
	//fScreen = new BScreen();
	fSlider = dynamic_cast<BSlider*>(FindView("brigth_slider"));
	prevValue = 10;
}

OutlineView::~OutlineView()
{
	delete fSlider;
	delete fDragger;
}


BArchivable *OutlineView::Instantiate(BMessage *data)
{
	return new OutlineView(data);
}

status_t
OutlineView::Archive(BMessage *archive, bool deep) const
{
	status_t status = BView::Archive(archive, deep);
	if (status == B_OK)
		status = archive->AddString("add_on", kAppSignature);
	if (status == B_OK)
		status = archive->AddString("class", "OutlineView");
	return status;
}


void
OutlineView::MessageReceived(BMessage *msg)
{
	switch (msg->what) {
		case B_ABOUT_REQUESTED:
		{
			BAlert *alert = new BAlert("about",
			"Brightnesser\nCopyright 2024\n\n\tby Fabio Tomat\n",
			"OK");
			alert->SetFlags(alert->Flags() | B_CLOSE_ON_ESCAPE);
			alert->Go();
			break;
		}
		default:
			BView::MessageReceived(msg);
			break;
	}
}
