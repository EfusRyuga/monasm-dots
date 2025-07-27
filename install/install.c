/*

This program is incomplete. Don't use it, it won't work lol.
 - Monasm 27/07/2025

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define size(x) sizeof(x)/sizeof(x[0])

char *dependency[] = {"git","hyprland","random_program"};

void boot(){
    printf("\033[33mStarting monasm-dots installation script");
    fflush(stdout);
    sleep(1);
    for(int i=0;i<3;i++){
        printf(".");
        fflush(stdout);
        sleep(1);
    }
    printf("\033[0m\n");
}

void dependencies(){
    printf("\033[33mChecking dependencies...\033[0m\n");
    for(int i=0;i<size(dependency);i++){
        char cmd[256],path[1024];
        FILE *pipe;
        snprintf(cmd,sizeof(cmd),"which %s 2>/dev/null",dependency[i]);
        pipe = popen(cmd,"r");
        printf("\033[33mFinding Dependency : %s\033[0m\n",dependency[i]);
        usleep(500000);
        if(fgets(path,sizeof(path),pipe)!=NULL){ 
            path[strcspn(path,"\n")]=0;
            printf("    \033[32mFound: %s at %s\033[0m\n",dependency[i],path);
        }
        else{
            printf("    \033[31mMissing dependency: %s\nRequirements unfulfilled (%d/%d). Ending Process...\033[0m\n",dependency[i],i,size(dependency));
            exit(EXIT_FAILURE);

        }
        pclose(pipe);
    }
}

int main(){
    setenv("PATH","/usr/local/sbin:/usr/local/bin:/usr/bin:/bin:/sbin:/usr/sbin",1);
    boot();
    dependencies();
}

