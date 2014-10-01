// A1 Unit Tests

#include "gtest/gtest.h"
#include "StopWatch.h"
#include "XApplication.h"

using namespace cs349;

TEST(A1UnitTestDemos, Construction) {
  StopWatch* watch = new StopWatch(XApplication::GetInstance()->GetEventQueue(), Rectangle(0, 0, 800, 300));
  EXPECT_FALSE(watch == NULL);
  EXPECT_FALSE(watch->IsRunning());

  EventQueue* queue = XApplication::GetInstance()->GetEventQueue();
  EXPECT_FALSE(queue == NULL);
  queue->ClearEventQueue(); // Need to clear the event queue of any
                            // events our watch window has generated,
                            // or else subsequent processing of those
                            // events will fail miserably (i.e., core
                            // dump) if events from the event queue
                            // are processed after the watch pointer
                            // is deleted below.

  delete watch;
}

unsigned long currenttime() {
  struct timespec tp;
  clock_gettime(CLOCK_REALTIME, &tp);
  return tp.tv_sec*1000 + tp.tv_nsec/1000000;
}

TEST(A1UnitTestDemos, Interaction) {
  StopWatch* watch = new StopWatch(XApplication::GetInstance()->GetEventQueue(), Rectangle(0, 0, 800, 300));
  EXPECT_FALSE(watch == NULL);
  watch->SetVisible(true);
  // Create a synthetic mouse event to test whether watch responds to it
  // or not. Note that this assumes that clicking in the location
  // specified amounts to pressing the start/stop button. Your actual
  // interaction will likely be different, making this test useless.
  // However, this should provide a template for how to do unit tests
  // for interaction.
  EXPECT_FALSE(watch->GetParentWindow() == NULL);
  //  MouseEvent* e = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(10, 10));
  MouseEvent* e1 = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseDown, Point(120,30)); //start
  MouseEvent* e2 = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(120,30));

  MouseEvent* e3 = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseDown, Point(170,30)); //pause
  MouseEvent* e4 = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(170,30));

  MouseEvent* e5 = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseDown, Point(220,30)); //reset
  MouseEvent* e6 = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(220,30));

  MouseEvent* e7 = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseDown, Point(120,30)); // start
  MouseEvent* e8 = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(120,30));

  MouseEvent* e9 = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseDown, Point(410,40)); // record
  MouseEvent* e10 = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(410,40));

  MouseEvent* e11 = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseDown, Point(170,30)); // pause
  MouseEvent* e12 = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(170,30));

  MouseEvent* e13 = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseDown, Point(120,30)); //start
  MouseEvent* e14 = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(120,30));

  MouseEvent* e15 = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseDown, Point(410,40)); //record
  MouseEvent* e16 = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(410,40));

  MouseEvent* e17 = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseDown, Point(170,30)); // pause
  MouseEvent* e18 = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(170,30));

  MouseEvent* e19 = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseDown, Point(220,30)); // reset
  MouseEvent* e20 = new MouseEvent(watch->GetParentWindow(), MouseEvent::mouseUp, Point(220,30));
    
  EventQueue* queue = XApplication::GetInstance()->GetEventQueue();
  EXPECT_FALSE(queue == NULL);
  
  EXPECT_FALSE(watch->IsRunning());
  queue->AddEventToQueue(e1);
  queue->AddEventToQueue(e2);
			  
  int Flag1 = 0;
  int Flag2 = 0;
  int Flag3 = 0;
  int Flag4 = 0;
  int Flag5 = 0;
  int Flag6 = 0;
  int Flag7 = 0;
  int Flag8 = 0;
  unsigned long start_time = currenttime();
  while (currenttime() - start_time < 100000)
    {
      XFlush(XApplication::GetInstance()->GetXDisplay());
      queue->ProcessNextEvent();
      if (currenttime() - start_time > 3000 && Flag1 == 0) {
	queue -> AddEventToQueue(e3);
	queue -> AddEventToQueue(e4);
	Flag1 = 1;
      }
      if (currenttime() - start_time > 6000 && Flag2 == 0) {
	queue -> AddEventToQueue(e5);
	queue -> AddEventToQueue(e6);
	Flag2 = 1;
      }
      if (currenttime() - start_time > 9000 && Flag3 == 0) {
	queue -> AddEventToQueue(e7);
	queue -> AddEventToQueue(e8);
	queue -> AddEventToQueue(e9);
	queue -> AddEventToQueue(e10);
	Flag3 = 1;
      }
      if (currenttime() - start_time > 14000 && Flag4 == 0) {
	queue -> AddEventToQueue(e11);
	queue -> AddEventToQueue(e12);
	Flag4 = 1;
      }
      if (currenttime() - start_time > 18000 && Flag5 == 0) {
	queue -> AddEventToQueue(e13);
	queue -> AddEventToQueue(e14);
	Flag5 = 1;
      }
      if (currenttime() - start_time > 50000 && Flag6 == 0) {
	queue -> AddEventToQueue(e15);
	queue -> AddEventToQueue(e16);
	Flag6 = 1;
      }
      if (currenttime() - start_time > 80000 && Flag7 == 0) {
	queue -> AddEventToQueue(e17);
	queue -> AddEventToQueue(e18);
	Flag7 = 1;
      }
      if (currenttime() - start_time > 90000 && Flag8 == 0) {
	queue -> AddEventToQueue(e19);
	queue -> AddEventToQueue(e20);
	Flag8 = 1;
      }
    }
  //  EXPECT_TRUE(watch->IsRunning());

  queue->ClearEventQueue();
  delete watch;
  // We do not need to delete the mouse event that we created, because
  // it will be deleted automatically by the EventQueue.
}
