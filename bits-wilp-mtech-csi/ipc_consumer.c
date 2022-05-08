#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// structure for message queue
struct msgq {
   long msg_type;
   char msg_text[100]; // max allowed length of message that can be sent
} message;

int main() {
   key_t mykey;
   int msgid;

   // using ftok to gneerate a uniqueue key, this will remain common key between producer and consumer of message queue
   mykey = ftok("./somefile", 10); 
   //  message queue using msgget and return the queue id
   msgid = msgget(mykey, 0666 | IPC_CREAT); 
   // receive message from queue using msgrcv
   msgrcv(msgid, &message, sizeof(message), 1, 0); 
   printf("Message received from queue is : %s \n", message.msg_text);
   // destroy the message queue
   msgctl(msgid, IPC_RMID, NULL);
   return 0;
}
