// Copyright (C) Alin Ichim 2023
#ifndef CONFIG_H_
#define CONFIG_H_

// Enables the logger (uncomment to activate).
#define SETLOG

// Logger functions.
#ifdef SETLOG
#define LOG_INIT(logfile) logger_init(logfile)
#define LOG_INFO(message) logger_info(message)
#define LOG_SUCCESS(message) logger_success(message)
#define LOG_ERROR(message) logger_error(message)
#else
#define LOG_INIT(logfile)
#define LOG_INFO(message)
#define LOG_SUCCESS(message)
#define LOG_ERROR(message)
#endif

// Output log file.
#define LOGFILE "logs/log_client.log"

// Server address.
#define HOST "34.254.242.81"
// Server port.
#define PORT 8080

#endif  // CONFIG_H_