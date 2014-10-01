#include <glog/logging.h>

#define TODO_LEVEL  70
#define PAINT_LEVEL 60
#define DEBUG_LEVEL 50
#define INFO_LEVEL  40
#define WARN_LEVEL  30

#define LOG_TODO  VLOG(TODO_LEVEL)
#define LOG_PAINT VLOG(PAINT_LEVEL)
#define LOG_DEBUG VLOG(DEBUG_LEVEL)
#define LOG_INFO  VLOG(INFO_LEVEL)
#define LOG_WARN  VLOG(WARN_LEVEL)
#define LOG_ERROR LOG(ERROR)
#define LOG_FATAL LOG(FATAL)
