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
        printf("Finding Dependency: %s\n",dependency[i]);
        usleep(100000);
        if(fgets(path,sizeof(path),pipe)!=NULL){ 
            path[strcspn(path,"\n")]=0;
            printf("    \033[92mFound: %s at %s\033[0m\n",dependency[i],path);
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
    snprintf(cmd,sizeof(cmd),"git clone %s",git_path);
    int status = system(cmd);
    if(status){
        printf("\033[31m\nFailed to clone repository from: %s\nProcess skipped!\033[0m\n",git_path);
    }
    else{
        printf("\033[92m\nSuccessfully cloned repository from: %s\033[0m\n",git_path);
    }
}

void warning(){
    char c;
    printf("\033[93mWARNING!!! The next procedure will overwrite **crucial Hyprland configuration files**.\nTo see which folders will be replaced, check out this repository:\n	%s\nAll the folders in the .config folder of this repository will be replacing all folders in your ~/.config directory. Before continuing, make sure to save any important files!\n\033[0m",git_path);
    while(!(c=='Y'||c=='y'||c=='N'||c=='n')){
        printf("\033[93mDo you wish to proceed (Y/N): \033[0m");
	scanf(" %c",&c);
	if((c=='Y'||c=='y'||c=='N'||c=='n')){
	    break;
	}
	else{
	    printf("\033[31mIncorrect input!\n\033[0m");
	}
    }
    if(c=='N'||c=='n'){
	printf("\033[92mEnding process...\033[0m\n");
	exit(EXIT_SUCCESS);
    }
}

int main(){
    setenv("PATH","/usr/local/sbin:/usr/local/bin:/usr/bin:/bin:/sbin:/usr/sbin",1);
    boot();
    dependencies();
    clone();
    warning();
}

