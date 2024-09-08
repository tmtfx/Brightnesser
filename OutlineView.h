#ifndef OUTLINEVIEW_H
#define OUTLINEVIEW_H

#include <stdio.h>
#include <TextView.h>
#include <Alert.h>

//#include <TranslationUtils.h>
#include <Dragger.h>
#include <View.h>
#include <Window.h>
#include <Screen.h>
#include <Slider.h>
#include <Message.h>



class _EXPORT OutlineView;

class OutlineView : public BView {
public:
						OutlineView(BRect frame);
						OutlineView(BMessage *data);
						~OutlineView();
	void				Pulse();
	virtual void 		MessageReceived(BMessage *msg);
	static 				BArchivable *Instantiate(BMessage *archive);
	virtual status_t 	Archive(BMessage *data, bool deep = true) const;
//	void				OutlineAboutRequested();
	BSlider		*fSlider;
	BScreen		*fScreen;
	

private:
	bool				fReplicated;
	BDragger*		fDragger;
	BMessage	*fMx;
//	int		conte;
};

#endif	// OUTLINE_VIEW_H
