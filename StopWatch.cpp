#include "XApplication.h"
#include "StopWatch.h"
#include <sstream>
#include <time.h>

using namespace std;

namespace cs349 {

  StopWatch::StopWatch(EventQueue* eventQueue, const Rectangle & bounds) : XWindow(string("Stop Watch!"), bounds) {
    this->running = false;
    this->timer = new Timer(eventQueue, 100, true, this);
    timer->Start();
    startTimeMS = 0;
  }

  StopWatch::~StopWatch() {
    timer->Stop();
    delete timer;
    timer = NULL;
  }

  unsigned long StopWatch::GetCurTime() {
    struct timespec tp;
    clock_gettime(CLOCK_REALTIME, &tp);
    return tp.tv_sec * 1000 + tp.tv_nsec / 1000000;
  }

  int minutes = 0;
  int seconds = 0;
  unsigned long milliseconds_temp = 0;
  unsigned long milliseconds = 0;
  unsigned long offset = 0;
  unsigned long offset1 = 0;
  bool checkreset = false;
  bool record_begin = false;
  void StopWatch::Paint(Graphics* g) {
// TODO CS349
    g->SetForegroundColor(XApplication::GetInstance()->GetBlackColor());
    g->FillRect(Rectangle(0,0,600,300));
    g->SetForegroundColor(XApplication::GetInstance()->GetWhiteColor());
    g->DrawRect(Rectangle(60,80,50,50));
    g->DrawRect(Rectangle(60,150,50,50));
    g->DrawRect(Rectangle(60,220,50,50));

    g->DrawRect(Rectangle(110,80,400,50));
    g->DrawRect(Rectangle(110,150,400,50));
    g->DrawRect(Rectangle(110,220,400,50));
    
    g->DrawRect(Rectangle(100,20,50,30));
    g->DrawRect(Rectangle(150,20,50,30));
    g->DrawRect(Rectangle(200,20,50,30));
    g->DrawRect(Rectangle(400,20,60,30));

    g->DrawText(Point(110,40),"START");
    g->DrawText(Point(160,40),"PAUSE");
    g->DrawText(Point(210,40),"RESET");
    g->DrawText(Point(410,40),"RECORD");
    g->DrawText(Point(30,110),"MIN");
    g->DrawText(Point(30,180),"SEC");
    g->DrawText(Point(10,250),"MILLISEC");
    
    if (checkreset) {
      milliseconds = 0;
      seconds = 0;
      minutes = 0;
      checkreset = false;
    }
   
    stringstream s1;
    stringstream s2;
    stringstream s3;
    s1 << minutes;
    s2 << seconds;
    s3 << milliseconds;
    g->DrawText(Point(80,110),s1.str());
    g->DrawText(Point(80,180),s2.str());
    g->DrawText(Point(80,250),s3.str());

    int visual_minutes = minutes;
    if (visual_minutes > 10) {
      visual_minutes = visual_minutes - 10;
    }

    g->FillRect(Rectangle(510-400*visual_minutes/10,80,400*visual_minutes/10,50));
    g->FillRect(Rectangle(510-400*seconds/60,150,400*seconds/60,50));
    g->FillRect(Rectangle(510-400*milliseconds/1000,220,400*milliseconds/1000,50));
    
    stringstream s4;
    stringstream s5;
    stringstream s6;
    
    //record option:
    if (record_begin == true) {
      int tmp1 = offset1%1000;
      int tmp2 = (offset1/1000)%60;
      unsigned long tmp3 = (offset1/1000)/60;

      s4 << tmp1;
      s5 << tmp2;
      s6 << tmp3;
    }
      g->DrawText(Point(500,40),s6.str());
      g->DrawText(Point(530,40),s5.str());
      g->DrawText(Point(560,40),s4.str());
   
    
    if(IsRunning()) {
      //  cout << "current offset: " << offset << endl;
      milliseconds_temp = GetCurTime() - (this->startTimeMS - offset);
      milliseconds = milliseconds_temp%1000;
      seconds = (milliseconds_temp/1000)%60;
      minutes = (milliseconds_temp/1000)/60;
      }  
  }

  int startdown = 0;
  int pausedown = 0;
  int resetdown = 0;
  int recorddown = 0;
  bool flag = true;

  bool StopWatch::HandleMouseEvent(const MouseEvent & e) {
    // TODO: Remove the following code and add your own event handling
    // code to handle mouse events
    LOG_DEBUG << "Received HandleMouseEvent in StopWatch" << e;

// TODO CS349
    switch(e.GetType()){
    case MouseEvent::MouseEvent::mouseUp:
      if (startdown == 0 && pausedown == 0 && resetdown == 0){
	break;
      }
      else if (e.GetWhere().x>=100 && e.GetWhere().x<150 && e.GetWhere().y>=20 && e.GetWhere().y<=50 && startdown == 1 && flag == true) {
	flag  = false;
	Start();
	break;
      }
      else if (e.GetWhere().x>=150 && e.GetWhere().x<200 && e.GetWhere().y>=20 && e.GetWhere().y<=50 && pausedown == 1) {
	Stop();
	startdown = 0;
	flag = true;
	offset = milliseconds_temp;
	break;
      }
      else if (e.GetWhere().x>=200 && e.GetWhere().x<250 && e.GetWhere().y>=20 && e.GetWhere().y<=50 && resetdown == 1 && pausedown == 1 && flag == true) {
       	offset = 0;
	checkreset = true;
	resetdown = 0;
	pausedown = 0;
	flag = true;
	Component::Repaint();
      }
      else if (e.GetWhere().x>=400 && e.GetWhere().x<460 && e.GetWhere().y>=20 && e.GetWhere().y<=60 && recorddown == 1) {
	record_begin = true;
	offset1 = milliseconds_temp;
	break;
      }	
      else {
	startdown = 0;
	pausedown = 0;
	resetdown = 0;
	break;
      }
    case MouseEvent::MouseEvent::mouseDown:
      if (e.GetWhere().x>=100 && e.GetWhere().x<150 && e.GetWhere().y>=20 && e.GetWhere().y<=50 && startdown == 0) {
	startdown = 1;
	break;
      }
      else if (e.GetWhere().x>=150 && e.GetWhere().x<200 && e.GetWhere().y>=20 && e.GetWhere().y<=50) {
	pausedown = 1;
	break;
      }
      else if (e.GetWhere().x>=200 && e.GetWhere().x<250 && e.GetWhere().y>=20 && e.GetWhere().y<=50) {
	resetdown = 1;
	break;
      }
      else if (e.GetWhere().x>=400 && e.GetWhere().x<460 && e.GetWhere().y>=20 && e.GetWhere().y<=60) {
	recorddown = 1;
	break;
      }	
      else {
	break;
      }
    case MouseEvent::MouseEvent::mouseMove:
      break;
    case MouseEvent::MouseEvent::mouseDrag:
      break;
    }
    return true;
  }

  void StopWatch::HandleTimerEvent(const cs349::TimerEvent & e) {
    if (running) {
      Component::Repaint();
    }
  }

  void StopWatch::Start() {
    this->running = true;
    startTimeMS = GetCurTime();
  }

  void StopWatch::Stop() {
    this->running = false;
  }

  bool StopWatch::IsRunning() const {
    return running;
  }
}
