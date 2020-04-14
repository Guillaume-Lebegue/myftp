/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** ftp_message
*/

#ifndef FTP_MESSAGE_H_
#define FTP_MESSAGE_H_

static const char ERROR_MALLOC[] = "Error malloc failed";

static const char ERROR_PARAM_DIR[] = "Given default path: Not a directory";
static const char ERROR_PARAM_PORT_NUM[] = "Given port: input isn't a number";

static const char ERROR_SOCKET_NOTFOUND[] =
    "!!!!Disconnected socket couldn't be found to delete!!!!";
static const char ERROR_SOCKET_READING[] =
    "New message: Error reading from socket";

static const char ERROR_SERVER_START[] = "Server couldn't start";
static const char ERROR_CONNECT[] = "Error with new connect";
static const char ERROR_MESSAGE[] = "Error with new message";

static const char INFO_SERVER_LISTEN[] = "Server now listening";
static const char INFO_SERVER_CLOSE[] = "Server now closing";

static const char WELCOME_MESSAGE[] = "Welcome on myftp";
static const char BYE_MESSAGE[] = "Bye.";

#endif /* !FTP_MESSAGE_H_ */
