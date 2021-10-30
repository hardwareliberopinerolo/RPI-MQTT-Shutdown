#include <stdio.h>
#include <string.h>
#include<stdlib.h>    // to use system() function
#include <mosquitto.h>

    /* Compile with:
    cc -o mqtt_shutdown_00  mqtt_shutdown_00.c -lmosquitto
     */


void shutdown(){
/*    
char ch;
    printf("Do you want to shutdown your pc now(y/n)?");
    scanf("%c", &ch);
    if(ch == 'y' || ch == 'Y'){ */
        system("shutdown -P now");
    //}
}

    void on_connect(struct mosquitto *mosq, void *userdata, int rc)
    {
        mosquitto_subscribe(mosq, NULL, "PC/poweroff/#", 0);
    }

    void on_message(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *m)
    {
        
        char* topic = m->topic;
        char* messaggio = m->payload;
        //printf("%s %s\n", topic, messaggio);

        if (!strcmp(topic,"PC/poweroff/" )) {
             //printf("%s \n", topic);
            
            if (!strcmp(messaggio,"off" )){
                 //printf("%s\n", messaggio);
                //printf("Spengo il PC! \n");
                shutdown();
                mosquitto_disconnect(mosq);
                
                 


                
            } 
        } 
    }


    int main(int argc, char **argv)
    {
        struct mosquitto *mosq;
        int rc;

        mosquitto_lib_init();

        mosq = mosquitto_new(NULL, true, (void *)NULL);
        if (!mosq) {
            fprintf(stderr, "Error: Out of memory.\n");
            mosquitto_lib_cleanup();
            return (1);
        }

        mosquitto_connect_callback_set(mosq, on_connect);
        mosquitto_message_callback_set(mosq, on_message);

        //rc = mosquitto_connect(mosq, "test.mosquitto.org", 1883, 60);
			rc = mosquitto_connect(mosq, "raspberrypi.local", 1883, 60);
        if (rc) {
            fprintf(stderr, "Unable to connect (%d).\n", rc);
            mosquitto_lib_cleanup();
            return (rc);
        }

        mosquitto_loop_forever(mosq, -1, 1);
        
        printf("Esco \n");

        /* Unreached */
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();

        return (0);
    }
