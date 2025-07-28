/*

This program is incomplete. Don't use it, it won't work lol.
 - Monasm 27/07/2025

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define size(x) sizeof(x)/sizeof(x[0])

char git_path[] = "https://github.com/Mon4sm/monasm-dots";
char *dependency[] = {"awk","basename","bash","brightnessctl","cat","cp","curl","cut","date","echo","eww","fastfetch","git","grep","grim","head","hyprctl","hypridle","hyprland","hyprlock","jq","kitty","loginctl","ls","mkdir","mv","nmcli","nvim","pamixer","pidof","playerctl","ranger","rm","sh","sleep","slurp","socat","stdbuf","systemctl","uptime","wget","wpctl","xargs"};

void boot(){
    printf("\033[93mStarting monasm-dots installation script");
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
    printf("\033[93mChecking dependencies...\033[0m\n");
    int cnt=0;
    for(int i=0;i<size(dependency);i++){
        char cmd[256],path[1024];
        FILE *pipe;
        snprintf(cmd,sizeof(cmd),"which %s 2>/dev/null",dependency[i]);
        pipe = popen(cmd,"r");
        printf("\033[93mFinding Dependency: %s\033[0m\n",dependency[i]);
        usleep(100000);
        if(fgets(path,sizeof(path),pipe)!=NULL){ 
            path[strcspn(path,"\n")]=0;
            printf("    \033[32mFound: %s at %s\033[0m\n",dependency[i],path);
        }
        else{
            sleep(1);
            printf("    \033[31mMissing dependency: %s\033[0m\n",dependency[i]);
            cnt++;
        }
        pclose(pipe);
    }
    if(cnt){
        printf("\033[31mRequirements unfulfilled. Missing dependencies (%d/%d). Ending process...\033[0m\n",cnt,size(dependency));
        exit(EXIT_FAILURE);
    }
}

void clone(){
    char cmd[128];
    snprintf(cmd,sizeof(cmd),"echo '\033[93m' && git clone %s && echo '\033[0m'",git_path);
    int status = system(cmd);
    if(status){
        printf("\033[31mFailed to clone repository from: %s\nProcess skipped!\033[0m\n",git_path);
    }
    else{
        printf("\033[32mSuccessfully cloned repository from: %s\033[0m\n",git_path);
    }
}

int main(){
    setenv("PATH","/usr/local/sbin:/usr/local/bin:/usr/bin:/bin:/sbin:/usr/sbin",1);
    boot();
    dependencies();
    clone();
}

