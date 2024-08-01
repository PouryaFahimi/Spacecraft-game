#include <windows.h>
#include <MMSystem.h>

void shot_sound(){
    PlaySound(TEXT("shot.wav"), NULL, SND_ASYNC);
}

void bonus_sound(){
    PlaySound(TEXT("bonus.wav"), NULL, SND_ASYNC);
}

void theme_sound(){
    PlaySound(TEXT("theme.wav"), NULL, SND_ASYNC);
}

void go_sound(){
    PlaySound(TEXT("gover.wav"), NULL, SND_ASYNC);
}