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
   // create message queue using msgget and return the queue id
   msgid = msgget(mykey, 0666 | IPC_CREAT); 
   message.msg_type = 1;
   printf("Write Message : ");
   fgets(message.msg_text, 100, stdin); // get input
   // send message to queue using mgssnd 
   msgsnd(msgid, &message, sizeof(message), 0); 
   printf("Message sent to queue is : %s \n", message.msg_text);
   return 0;
}
