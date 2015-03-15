// Copyright (c) 2015, Thjafa <thjalfa@libero.it>
// All rights reserved.

// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include  <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <stddef.h>

#define INVNUM 10
#define DEBUG 1

#ifdef __APPLE__ && __MACH__ /*MacOSX*/
#define OS 0
#endif /*__APPLE__ && __MACH__*/

#ifdef _WIN32 /*Windows 32-bit or 64-bit*/
#define OS 1
#endif /*_WIN32*/

#ifdef __gnu_linux__ /*GNU/Linux*/
#define OS 2
#endif /*__gnu_linux__*/

//test ifdef

void treasure(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* future, int* map, int* loot, int* vision, int* end, int* pos, int* antimag, int rec, int stat, int combat);

void magic(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* future, int* map, int* loot, int* vision, int* end, int* pos, int* floor, int* start, int* antimag, int* checkcurse, int combat, int* control, int* contator, int* modenemy, int* datt, int* modatt, int* nomag, char* s);

int magicconsume(int* aces, int* inv, int cost, char* name);

void stonestatue(int* aces, int* inv, int* map, int times, int combat, int free);

void godvision(int* aces, int* inv, int* vision, int* nomag, int free);

int getint(int *i) {
    int nope=0;
    int end;
    char buffer[100];
    do {
        if (nope==1)
            fputs("Invalid input, try again.\n", stdout);
        nope=1;
        if (NULL==fgets(buffer,sizeof(buffer),stdin))
            return -1;
        errno=0;
    } while ((1!=sscanf(buffer,"%d %n",i,&end))||buffer[end]||errno);
    return 0;
}

void shiftarray(int* a) {
    int i;
    for (i=0; i<INVNUM-1; i++) *(a+i)=*(a+i+1);
    *(a+INVNUM-1)=-1;
}

void hebrac(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* future, int* map, int* loot, int* vision, int* end, int* pos, int* antimag, int rec, int stat, int combat) {
    struct timespec a;
    a.tv_sec  = 0;
    a.tv_nsec = 1000;
    nanosleep( &a, NULL );
    struct timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);
    int r,i=0;
    do {
        printf("Hebrac itself is in front of you!\n'Do you want to play? It's a coin flip: you can get some nice treasure or you can get hurt...'\n[0]: Don't play\n[1]: Heads\n[2]: Tails\n");
        getint(&r);
        if ((r!=0)&&(r!=1)&&(r!=2)) {
            if (i==0) {
                printf("'I don't have all the day...'\n");
                i=1;
            } else if (i>0) {
                printf("'Don't be rude the next time!'\nHebrac disappears!\n");
                *(loot+*pos)=-1;
                *(vision+*pos)=2;
                return;
            }
        }
    } while ((r!=0)&&(r!=1)&&(r!=2));
    printf("'As you wish...'\n");
    if (r==0) {
        printf("Hebrac disappears!\n");
        *(loot+*pos)=-1;
        *(vision+*pos)=2;
        return;
    }
    i=rand()%2;
    if (*future>=0) {
        printf("Do you think that your divination skills can surpass my power?\n");
        shiftarray(future);
    }
    if (i==0) {
        if (r==1) {
            printf("Tails! You lose 5 HP!\nHebrac disappears!\n");
        }
        else {
            printf("Heads! You lose 5 HP!\nHebrac disappears!\n");
        }
        *(loot+*pos)=-1;
        *(vision+*pos)=2;
        *hpnow=*hpnow-5;
        return;
    } else {
        if (r==1) {
            printf("Heads! You can take the treasure!\nHebrac disappears!\n");
        }
        else {
            printf("Tails! You can take the treasure!\nHebrac disappears!\n");
        }
        treasure(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag,rec,stat,combat);
    }
}

void genie(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* future, int* map, int* loot, int* vision, int* end, int* pos, int* antimag, int r, int combat) {
    if (r==12) {
        printf("You rub the lantern! From the smoke, a djinn of Life appears!\nYour maximum HP are increased by 2!\n");
        *hpmax=*hpmax+2;
        return;
    }
    if (r==25) {
        printf("You rub the lantern! From the smoke, a djinn of Luck appears!\nYou find some treasure!\n");
        treasure(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag,1,0,combat);
        treasure(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag,1,0,combat);
        treasure(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag,1,0,combat);
        return;
    }
    if (r==38) {
        printf("You rub the lantern! From the smoke, a djinn of Destiny appears!\nNow you know this floor perfectly!\n");
        godvision(aces,inv,vision,NULL,1);
        return;
    }
    printf("You rub the lantern! From the smoke, a djinn of Death appears!\nYou can choose to kill 3 enemies!\n");
    stonestatue(aces,inv,map,3,combat,1);
}

int checkpositiveinv(int* a) {
    int i;
    for (i=0; i<INVNUM; i++) {
        if (*(a+i)>0) return 1;
    }
    return 0;
}

int checkpositiveace(int* a) {
    int i;
    for (i=0; i<4; i++) {
        if (*(a+i)>0) return 1;
    }
    return 0;
}

int checkfullinv(int* a) {
    int i;
    for (i=0; i<INVNUM; i++) {
        if (*(a+i)==0) return i;
    }
    return -1;
}

int value(int card) {
    switch (card) {
        case 22: return 40;
        case 21: return 39;
        case 20: return 38;
        case 9: return 37;
        case 8: return 36;
        case 19: return 35;
        case 35: return 34;
        case 34: return 33;
        case 48: return 32;
        case 47: return 31;
        case 7: return 30;
        case 33: return 29;
        case 18: return 28;
        case 6: return 27;
        case 46: return 26;
        case 32: return 25;
        case 45: return 24;
        case 17: return 23;
        case 31: return 22;
        case 5: return 21;
        case 44: return 20;
        case 4: return 19;
        case 30: return 18;
        case 43: return 17;
        case 15: return 16;
        case 3: return 15;
        case 29: return 14;
        case 16: return 13;
        case 14: return 12;
        case 2: return 11;
        case 1: return 10;
        case 28: return 9;
        case 27: return 8;
        case 42: return 7;
        case 41: return 6;
        case 40: return 5;
        default: return -1;
    }
}

int leastvalueinv(int* inv) {
    int min=-1;
    int pos;
    for (pos=0; pos<INVNUM; pos++) {
        if (min<0) {
            if (*(inv+pos)>0) min=pos;
        }
        else if ((value(*inv+min)>value(*inv+pos))&&(value(*inv+pos)>0)) min=pos;
    }
    return min;
}

void nameitem(char* s, int i) {
    memset(s,0,sizeof(s));
    if (i==0) {
        sprintf(s,"Ruby of Gaza");
        return;
    }
    if (i==26) {
        sprintf(s,"Scepter of Leynos");
        return;
    }
    if (i==39) {
        sprintf(s,"Bracelet of Armok");
        return;
    }
    if (i%13==10) {
        sprintf(s,"prisoner");
        return;
    }
    if (i%13==11) {
        sprintf(s,"white priestess");
        return;
    }
    if (i==12) {
        sprintf(s,"djinn of Life");
        return;
    }
    if (i==25) {
        sprintf(s,"djinn of Luck");
        return;
    }
    if (i==38) {
        sprintf(s,"djinn of Destiny");
        return;
    }
    if (i==51) {
        sprintf(s,"djinn of Death");
        return;
    }
    if (i<12) {
        sprintf(s,"%d life potions",i%13+1);
        return;
    }
    if (i<25) {
        sprintf(s,"%d gems",i%13+1);
        return;
    }
    if (i<38) {
        sprintf(s,"%d magic potions",i%13+1);
        return;
    }
    if (i<51) sprintf(s,"%d strength potions",i%13+1);
}

void removeleast(int* hpmax, int* hpnow, int* aces, int* inv) {
    if (!checkpositiveinv(inv)) {
        if (!checkpositiveace(aces)) {
            printf("'Your bag is empty!'\nThe black priestess disappears!\n");
            return;
        }
        if (*(aces+3)==1) {
            *(aces+3)=0;
            printf("'I'm sorry, but I have to take your Bracelet of Armok.'\nThe black priestess disappears!\n");
            return;
        }
        if (*(aces+2)==1) {
            *(aces+2)=0;
            printf("'I'm sorry, but I have to take your Scepter of Leynos.'\nThe black priestess disappears!\n");
            return;
        }
        if (*(aces)==1) {
            *(aces)=0;
            printf("'I'm sorry, but I have to take your Ruby of Gaza.'\nThe black priestess disappears!\n");
            *hpmax=*hpmax-5;
            *hpnow=min(*hpmax,*hpnow);
            return;
        }
        if (*(aces+1)==1) {
            *(aces+1)=0;
            printf("'I'm sorry, but I have to take your Bag of Meres.'\nThe black priestess disappears!\n");
            return;
        }
    }
    int p=leastvalueinv(inv);
    char s[20];
    nameitem(s,*(inv+p));
    printf("'I'm sorry, but I have to take your %s.'\nThe black priestess disappears!\n",s);
    *(inv+p)=0;
}

int mostvalueinv(int* inv) {
    int max=-1;
    int pos;
    for (pos=0; pos<INVNUM; pos++) {
        if (max<0) {
            if ((*(inv+pos)>0)&&(*(inv+pos)%13!=10)) max=pos;
        }
        else if ((*(inv+pos)%13!=10)&&(value(*inv+max)<value(*inv+pos))) max=pos;
    }
    return max;
}

void removemost(int* hpmax, int* hpnow, int* aces, int* inv) {
    if (checkpositiveace(aces)) {
        if (*(aces+1)==1) {
            *(aces+1)=0;
            printf("'Nice, I will take your Bag of Meres.'\nThe black priestess disappears!\n");
            return;
        }
        if (*(aces)==1) {
            *(aces)=0;
            printf("'Nice, I will take your Ruby of Gaza.'\nThe black priestess disappears!\n");
            *hpmax=*hpmax-5;
            *hpnow=min(*hpmax,*hpnow);
            return;
        }
        if (*(aces+2)==1) {
            *(aces+2)=0;
            printf("'Nice, I will take your Scepter of Leynos.'\nThe black priestess disappears!\n");
            return;
        }
        if (*(aces+3)==1) {
            *(aces+3)=0;
            printf("'Nice, I will take your Bracelet of Armok.'\nThe black priestess disappears!\n");
            return;
        }
    }
    if (!checkpositiveinv(inv)) {
        printf("'Damn, your bag is empty!'\nThe black priestess disappears!\n");
        return;
    }
    int p=mostvalueinv(inv);
    if (p=0) {
        printf("'I can't take anything from you!'\nThe black priestess disappears!\n");
        return;
    }
    char s[20];
    nameitem(s,*(inv+p));
    printf("'Not bad, I will take your %s.'\nThe black priestess disappears!\n",s);
    *(inv+p)=0;
}

void blackqueen(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* future, int* map, int* loot, int* vision, int* end, int* pos, int* antimag, int good) {
    printf("It is a black priestess, a kleptomaniac demon!\n");
    if (*antimag==1) {
        printf("Because the antimagic field, the black magic of the priestess is uneffective!\n");
        return;
    }
    if (good==1) {
        printf("'Because you freed me, I will take your cheapest item with my black magic...'\n");
        removeleast(hpmax,hpnow,aces,inv);
        return;
    }
    printf("'Ah, I will take something expensive from you!'\n");
    removemost(hpmax,hpnow,aces,inv);
    treasure(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag,0,1,0);
}

void redqueen(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* future, int* map, int* loot, int* vision, int* end, int* pos, int* antimag, int rec, int stat, int combat) {
    int i;
    printf("You meet a white priestess, a gentle pixie!\n'Greetings! I want to help you, but you don't have to be greedy. Do you want a gift or you want to be healed?'\n");
    if (*antimag==1) {
        printf("'Wait! I perceive an antimagic field, so I can't heal you... here a gift, I hope it will be useful...'\n");
        treasure(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag,rec,stat,combat);
        return;
    } else {
        printf("[0]: Gift\n[1]: Heal\n");
    }
    do {
        getint(&i);
        if (i==0) {
            printf("'As you wish, here your gift!'\nThe white priestess disappears!\n");
            treasure(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag,rec,stat,combat);
            return;
        }
        if (i==1) {
            printf("'As you wish, I will heal you!'\nThe white priestess disappears!\n");
            *hpnow=*hpmax;
            *(loot+*pos)=-1;
            *(vision+*pos)=2;
            return;
        }
        printf("'I'm sorry, but I can't understand you... Do you want a gift or you want to be healed?'\n[0]: Gift\n[1]: Heal\n'");
        i=-1;
    } while (i==-1);
}

void addslave(int* slave) {
    printf("A prisoner stands before you.\n'Thanks! Thanks so much! Because you freed me, I will help in a battle!'\n");
    int i;
    for (i=0; i<INVNUM; i++) {
        if (*(slave+i)==0) *(slave+i)=1;
        return;
    }
    printf("'...but it seems that your group is too much large and there isn't a place for me.'");
}

void addaces(int* hpmax, int* aces, int a) {
    printf("Is this one of the four artifacts?!\n");
    if (a<9) a=0;
    else if (a<22) a=1;
    else if (a<35) a=2;
    else a=3;
    if (*(aces+a)) {
        printf("It is only a pathetic imitation...\n");
        return;
    }
    *(aces+a)=1;
    if (a==0) {
        printf("You found the Ruby of Gaza!\n");
        *hpmax=*hpmax+5;
    }
    else if (a==1) {
        printf("You found the Bag of Meres!\n");
    }
    else if (a==2) {
        printf("You found the Scepter of Leynos!\n");
    }
    else {
        printf("You found the Bracelet of Armok!\n");
    }
}

void dropinv(int* inv, int r) {
    int i;
    char s[20];
    char t[20];
    nameitem(s,r);
    printf("Your bag is full! Do you want to drop something to keep %s?\n[0]: No\n[1]: Yes\n",s);
    getint(&i);
    if (i==0) {
        printf("You don't keep the %s.\n",s);
    } else {
        i=0;
        do {
            printf("What do you want to drop?\n");
            getint(&i);
            if ((i<0)||(i>=INVNUM)) {
                printf("You don't have that slot! Insert a number between 0 and %d!\n",INVNUM-1);
                i=0;
            } else {
                int k;
                nameitem(t,*(inv+i));
                printf("Do you want to drop the %s?\n[0]: No\n[1]: Yes\n",t);
                getint(&k);
                if (k==1) {
                    printf("You dropped the %s to keep the %s.\n",s,t);
                    *(inv+i)=r;
                    i=-1;
                    return;
                } else if (k!=0) {
                    printf("You don't have all the day to decide...\n");
                }
            }
        } while (i!=-1);
    }
    printf("What do you want to drop?\n");
}

void treasure(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* future, int* map, int* loot, int* vision, int* end, int* pos, int* antimag, int rec, int stat, int combat) {
    struct timespec a;
    a.tv_sec  = 0;
    a.tv_nsec = 1000;
    nanosleep( &a, NULL );
    struct timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);
    int r,n;
    if (stat==0) {
        if (*future>=0) {
            r=*future;
            shiftarray(future);
        }
        else r=rand()%54;
    }
    else r=*(loot+*pos);
    if (r==-1) {
        printf("This room is empty...\n");
        return;
    }
    if (stat==1) {
        printf("Do you want to take the treasure in this room?\n[0]: No\n[1]: Yes\n");
        getint(&n);
        if (n==0) return;
    }
    if (r>=52) hebrac(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag,rec,0,combat);
    else if (r%13==12) {
        if (rec==0) genie(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag,r,combat);
        else {
            printf("An empty lantern...");
        }
    }
    else if (r%13==11) {
    if (r>=25) blackqueen(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag,1);
    else redqueen(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag,rec,0,combat);
    }
    else if (r%13==10) addslave(slave);
    else if (r%13==0) addaces(hpmax,aces,r);
    else {
        int n=checkfullinv(inv);
        char s[20];
        if (n>=0) {
            *(inv+n)=r;
            nameitem(s,r);
            printf("You received %s!\n",s);
        } else {
            dropinv(inv,r);
        }
    }
    if (stat==1) {
        *(loot+*pos)=-1;
        *(vision+*pos)=2;
    }
}

int valueitem(int n) {
    if (n>51) return 2;
    if (n%13==0) return 12;
    if (n%13==10) return 8;
    if (n%13==11) return 9;
    if (n%13==12) return 10;
    if ((n>25)&&(n<39)) return 2*(n%13+1);
    return n%13+1;
}

int gemcount(int* inv) {
    int value=0;
    int i;
    for (i=0; i<INVNUM; i++) {
        if ((*(inv+i)>12)&&(*(inv+i)<22)) value+=(*(inv+i)%13)+1;
    }
    return value;
}

int valueinv(int* inv, int* slave) {
    int i;
    int value=0;
    for (i=0; i<INVNUM; i++) {
        if (*(inv+i)) value+=valueitem(*(inv+i));
        value+=8*(*(slave+i));
    }
    return value;
}

int numslav(int* slave) {
    int i;
    int n=0;
    for (i=0; i<INVNUM; i++) {
        n+=*(slave+i);
    }
    return n;
}

void removeslave(int* slave, int n) {
    int i;
    for (i=INVNUM-1; i>=0; i--) {
        if (*(slave+i)) {
            *(slave+i)=0;
            n--;
        }
        if (n==0) return;
    }
}

void goodsoffer(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* future, int* map, int* loot, int* vision, int* end, int* pos, int* antimag) {
    int value=0;
    int k;
    int offitem[INVNUM];
    for (k=0; k<INVNUM; k++) {
        offitem[k]=0;
    }
    int offslav;  
    char s[20];
    int p=-1;
    do {
        printf("'What do you want to offer? An item or a slave?'\n[0]: Item\n[1]: Slave\n");
        getint(&k);
        if (k==0) {
            printf("'What item do you want to offer?'\n");
            getint(&k);
            if ((k<0)||(k>=INVNUM)||(*(inv+k)==0)) {
                printf("'Are you kidding me? Do you want to abort the trade?'\n[0]: No\n[1]: Yes\n");
                getint(&k);
                if (k==1) {
                    printf("You aborted the trade.\n");
                    return;
                }
            } else {
                value+=valueitem(*(inv+k));
                p++;
                offitem[p]=*(inv+k);
            }
        } else if (k==1) {
            if (offslav>=numslav(slave)) {
                printf("'You don't have enough slaves to offer!\n'");
            } else {
                offslav++;
                value+=8;
            }
        } else {
            printf("'Are you kidding me? Do you want to abort the trade?'\n[0]: No\n[1]: Yes\n");
            getint(&k);
            if (k==1) {
                printf("You aborted the trade.\n");
                return;
            }
        }
        if (value<valueitem(*(loot+*pos))) printf("'My item is valued %d gems and you offer is worth %d gems.'\n",valueitem(*(loot+*pos)),value);
        else {
            printf("'I'm satisfied with your offer of %d slaves and",offslav);
            for (k=0; k<=p; k++) {
                nameitem(s,offitem[k]);
                printf(" %s",s);
                if (k<p) {
                    printf(",");
                }
                else {
                    printf(".");
                }
            }
            if (p<0) {
                printf("nothing else.'\n");
            }
            else {
                printf(".'\n");
            }
            k=-1;
            do {
                printf("'Do you accept the trade?'\n[0]: No\n[1]: Yes\n");
                getint(&k);
                if (k==0) {
                    printf("'Do you want to abort the trade?'\n[0]: No\n[1]: Yes\n");
                    getint(&k);
                    if (k==1) {
                        printf("You aborted the trade.\n");
                        return;
                    }
                    printf("'Do you want to propose another offer?'\n[0]: No\n[1]: Yes\n");
                    if (k==0) {
                        printf("You aborted the trade.\n");
                        return;
                    }
                    for (k=0; k<INVNUM; k++) {
                        offitem[k]=0;
                    }
                    offslav=0;
                    p=-1;
                } else if (k==1) {
                    removeslave(slave,offslav);
                    for (k=0; k<=p; k++) {
                        *(inv+offitem[k])=0;
                    }
                    treasure(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag,0,1,0);
                }
            } while (k<0);
        }
    } while (value<valueitem(*(loot+*pos)));
}

void gemoffer(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* future, int* map, int* loot, int* vision, int* end, int* pos, int* antimag) {
    int value=0;
    int k;
    int offgem[INVNUM];
    for (k=0; k<INVNUM; k++) {
        offgem[k]=0;
    }
    char s[20];
    int p=-1;
    do {
        printf("'What gem do you want to offer?'\n");
        getint(&k);
        if ((k<0)||(k>=INVNUM)||(*(inv+k)==0)) {
            printf("'Are you kidding me? Do you want to abort the trade?'\n[0]: No\n[1]: Yes\n");
            getint(&k);
            if (k==1) return;
        } else if ((*(inv+k)>22)||(*(inv+k)<14)) {
            printf("'That's not a gem! Do you want to abort the trade?'\n[0]: No\n[1]: Yes\n");
            getint(&k);
            if (k==1) {
                printf("You aborted the trade.\n");
                return;
            }
        } else {
            value+=*(inv+k)%13;
            p++;
            offgem[p]=*(inv+k);
        }
        if (value<valueitem(*(loot+*pos))) printf("'My item is valued %d gems and you offer is worth %d gems.'\n",valueitem(*(loot+*pos)),value);
        else {
            printf("'I'm satisfied with your offer of %d gems:",value);
            for (k=0; k<=p; k++) {
                nameitem(s,offgem[k]);
                if (k==p) {
                    printf(" %s gems.'\n",s);
                } else {
                    printf(" %s gems,",s);
                }
            }
            k=-1;
            do {
                printf("'Do you accept the trade?'\n[0]: No\n[1]: Yes\n");
                getint(&k);
                if (k==0) {
                    printf("'Do you want to abort the trade?'\n[0]: No\n[1]: Yes\n");
                    getint(&k);
                    if (k==1) {
                        printf("You aborted the trade.\n");
                        return;
                    }
                    printf("'Do you want to propose another offer?'\n[0]: No\n[1]: Yes\n");
                    if (k==0) {
                        printf("You aborted the trade.\n");
                        return;
                    }
                    for (k=0; k<INVNUM; k++) {
                        offgem[k]=0;
                    }
                    p=-1;
                } else if (k==1) {
                    for (k=0; k<=p; k++) {
                        *(inv+offgem[k])=0;
                    }
                    treasure(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag,0,1,0);
                }
            } while (k<0);
        }
    } while (value<valueitem(*(loot+*pos)));
}

int illusion(int* aces, int* inv) {
    char s[20];
    memset(s,0,sizeof(s));
    sprintf(s,"Illusion");
    int v=magicconsume(aces,inv,4,s);
    if (v<0) return 0;
    return 1;
}

void stealingspirit(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* future, int* map, int* loot, int* vision, int* end, int* pos, int* floor, int* start, int* antimag, int* checkcurse, char* st, int* control);

void exchange(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* future, int* map, int* loot, int* vision, int* end, int* pos, int* floor, int* start, int* antimag, int type) {
    char s[20];
    int i;
    nameitem(s,*(loot+*pos));
    if (*(aces+1)==1) {
        printf("You put out enough gems from your bag of Meres and buy the %s.\n",s);
        treasure(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag,0,1,0);
        return;
        }
    if ((type==1)&&(magiccount(aces,inv)>3)) {
        printf("Do you want to use an Illusion spell?\n[0]: No\n[1]: Yes\n");
        getint(&i);
        if (i==1) i=illusion(aces,inv);
        if (i==1) {
            printf("You give nothing to the adventurer, but you receive the treasure!\n");
            treasure(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag,0,1,0);
        }
    }
    if (magiccount(aces,inv)>5) {
        printf("Do you want to use a StealingSpirit spell?\n[0]: No\n[1]: Yes\n");
        getint(&i);
        if (i==1) {
            stealingspirit(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,floor,start,antimag,NULL,NULL,NULL);
            if (type==0) {
                printf("The merchant disappears!\n");
            }
        }
    }
    if (valueitem(*(loot+*pos))>valueinv(inv,slave)) {
        printf("'You don't have enough goods to trade!'\n");
        *(loot+*pos)=-1;
        *(vision+*pos)=2;
        return;
    }
    if ((type==1)&&(valueitem(*(loot+*pos))>gemcount(inv))) {
        printf("'You don't have enough gems to trade!'\n");
        *(loot+*pos)=-1;
        *(vision+*pos)=2;
        return;
    }
    if (type==0) {
        goodsoffer(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag);
        return;
    }
    gemoffer(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag);
}


void trade(int* hpmax, int* hpnow, int* aces, int* inv, int* future, int* slave, int* map, int* loot, int* vision, int* end, int* pos, int* floor, int* start, int* antimag, int type) {
    int i;
    if ((type==1)&&(*(loot+*pos)>13)&&(*(loot+*pos)<23)) {
        printf("'I'm sorry, but I have already sold my goods.'\n");
        if (magiccount(aces,inv)>5) {
            printf("Do you want to use a StealingSpirit spell?\n[0]: No\n[1]: Yes\n");
            getint(&i);
            if (i==1) {
                stealingspirit(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,floor,start,antimag,NULL,NULL,NULL);
                if (type==0) {
                    printf("The merchant disappears!\n");
                }
            }
        }
        *(loot+*pos)=-1;
        *(vision+*pos)=2;
        return;
    }
    if ((type==0)&&(*(loot+*pos)%13==0)) {
        printf("'I'm sorry, but I don't want to trade my artifact.'\n");
        *(loot+*pos)=-1;
        *(vision+*pos)=2;
        return;
    }
    if ((*(loot+*pos)%13==11)&&(*(loot+*pos)>25)) {
        printf("'I don't think you are interest in a black priestess...'\n");
        *(loot+*pos)=-1;
        *(vision+*pos)=2;
        return;
    }
    char s[20];
    nameitem(s,*(loot+*pos));
    do {
        printf("'Are you interested in my %s?'\n",s);
        if (*(loot+*pos)%13==0) {
            if (((*(loot+*pos)==0)&&(*aces==1))||((*(loot+*pos)==13)&&(*(aces+1)==1))||((*(loot+*pos)==26)&&(*(aces+2)==1))||((*(loot+*pos)==39)&&(*(aces+3)==1))) {
                printf("You see it's only a pathetic imitation...\n");
                *(loot+*pos)=-1;
                *(vision+*pos)=2;
                return;
            }
        }
        printf("[0]: No\n[1]: Yes\n");
        getint(&i);
        if (i==0) {
            *(loot+*pos)=-1;
            *(vision+*pos)=2;
            return;
        }
        if (i==1) {
            exchange(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,floor,start,antimag,type);
            *(vision+*pos)=2;
            *(loot+*pos)=-1;
            return;
        }
        else {
            i=-1;
            printf("'What?'\n");
        }
    } while (i=-1);
}

int hit(int* future) {
    struct timespec a;
    a.tv_sec  = 0;
    a.tv_nsec = 1000;
    nanosleep( &a, NULL );
    struct timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);
    int k;
    if (*future>=0) {
        k=*future;
        shiftarray(future);
    } else k=rand()%13;
    if (k>8) return 10;
    return k+1;
}

int max(int a, int b) {
    if (a>b) return a;
    return b;
}

void nameenemy(char* s, int enemy) {
    memset(s,0,sizeof(s));
    if (enemy%13==10) sprintf(s,"adventurer");
    else if (enemy<13) sprintf(s,"amazon");
    else if (enemy<26) sprintf(s,"demon");
    else if (enemy<39) sprintf(s,"magician");
    else sprintf(s,"warrior");
}

int min(int a, int b) {
    if (a<b) return a;
    return b;
}

void useitemcombat(int* hpmax, int* hpnow, int* inv, int* slave, int* bonusnext, int* bonuscomb) {
    int k=-1;
    char s[20];
    printf("Do you want to use an item or seek help from a prisoner?\n[0]: Item\n[1]: Prisoner\n");
    getint(&k);
    if (k==0) {
        printf("What item do you want to use?\n");
        getint(&k);
        if ((k<0)||(k>=INVNUM)||(*(inv+k)==0)) {
            printf("Maybe you are a little too much excited for this fight!\n");
            return;
        } else if (*(inv+k)<14) {
            if (*hpmax==*hpnow) {
                printf("Not really useful now...\n");
                return;
            }
            nameitem(s,*(inv+k));
            printf("You use %s!\n",s);
            *hpnow=min(*hpmax,*hpnow+(*(inv+k)%13)+1);
            *(inv+k)=0;
        } else if (*(inv+k)<27) {
            printf("Gems are nice, but not really useful in a fight!\n");
            return;
        } else if (*(inv+k)<40) {
            printf("If you want to do magic, maybe you have to cast a spell...\n");
            return;
        } else {
            nameitem(s,*(inv+k));
            printf("You use %s!\n",s);
            *bonusnext=*bonusnext+(*(inv+k)%13)+1;
            *(inv+k)=0;
        }
    } else if (k==1) {
        if (!checkpositiveinv(slave)) {
            printf("There aren't other adventures with you!\n");
            return;
        } else {
            *bonuscomb=*bonuscomb+3;
            removeslave(slave,1);
            printf("A prisoner join your fight for his freedom!\n");
        }
    } else {
        printf("Maybe you are a little too much excited for this fight!\n");
    }
}

int combat(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* future, int* map, int* loot, int* vision, int* end, int* pos, int* floor, int* start, int* antimag, int* checkcurse, int* nomag, int enemy) {
    char s[10];
    nameenemy(s,enemy);
    int hpenemy=enemy%13+1;
    if (enemy==0) hpenemy=10;
    if (*checkcurse) {
        int a=hpenemy%2;
        hpenemy=hpenemy/2+a;
    }
    printf("An enemy %s appears! It has %d HP!\n",s,hpenemy);
    int e=0;
    int k;
    int control=1;
    int bonusnext=0;
    int bonuscomb=0;
    int bonusaces=0;
    int modenemy=1;
    if ((*antimag==1)&&(enemy>26)&&(enemy<36)) modenemy=0;
    int contator=0;
    int datt=0;
    int modatt=1;
    if (*nomag==2) *nomag=1;
    if (*(aces+3)) bonusaces=3;
    do {
        printf("What do you want to do?\n[0]: Attack\n[1]: Magic\n[2]: Items\n");
        getint(&k);
        if (k==0) {
            k=hit(future)*modatt+bonusnext+bonuscomb+bonusaces;
            hpenemy-=k;
            hpenemy=max(hpenemy,0);
            printf("You strike the %s for %d damage! It has %d HP!\n",s,k,hpenemy);
            if (datt==1) {
                k=hit(future)+bonusnext+bonuscomb+bonusaces;
                hpenemy-=k;
                hpenemy=max(hpenemy,0);
                datt=0;
                printf("You perform a second attack and strike the %s for %d damage! It has %d HP!\n",s,k,hpenemy);
            }
            if (hpenemy==0) {
                e=1;
                treasure(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag,0,1,0);
            }
            else {
                k=hpenemy*modenemy;
                *hpnow=*hpnow-k;
                *hpnow=max(*hpnow,0);
                if (contator>0) {
                    printf("The %s is paralysed!\n",s);
                }
                else if ((*antimag==1)&&(enemy>26)&&(enemy<36)) {
                    printf("The attack of the %s is blocked by the antimagic field!\n",s);
                }
                else {
                    printf("The %s strikes you for %d damage! You have %d HP!\n",s,k,*hpnow);
                }
                if (*hpnow<=0) e=1;
            }
        } else if (k==1) {
            magic(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,floor,start,antimag,checkcurse,1,&control,&contator,&modenemy,&datt,&modatt,nomag,s);
        } else if (k==2) {
            useitemcombat(hpmax,hpnow,inv,slave,&bonusnext,&bonuscomb);
        } else {
            printf("What do you want to do?! It is really an uneasy moment...\n");
        }
        if (*start==1) e=1;
        if (contator>0) {
            contator--;
            if (contator==0) modenemy=1;
        }
    } while (e==0);
    if (*nomag!=2) *nomag=0;
    return control;
}

void adventurer(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* future, int* map, int* loot, int* vision, int* end, int* pos, int* floor, int* start, int* antimag, int* checkcurse, int* nomag, int* control) {
    struct timespec a;
    a.tv_sec  = 0;
    a.tv_nsec = 1000;
    nanosleep( &a, NULL );
    struct timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);
    int i;
    printf("It's another adventurer! Do you want to battle ");
    i=rand()%2;
    if (i==0) {
        printf("her ");
    }
    else {
        printf("him ");
    }
    printf("or you want to trade something?\n");
    if (*(loot+*pos)==-1) {
        printf("The adventurer recognise you! You have to fight!\n");
        *control=combat(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,floor,start,antimag,checkcurse,nomag,10);
    } else {
        printf("[0]: Battle\n[1]: Trade\n");
        do {
            getint(&i);
            if (i==0) *control=combat(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,floor,start,antimag,checkcurse,nomag,10);
            else if (i==1) trade(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,floor,start,antimag,0);
            else {
                printf("The adventurer didn't understand your intentions! Do you want to battle or to trade?\n[0]: Battle\n[1]: Trade\n");
                i=-1;
            }
        } while ((i!=0)&&(i!=1));
    }
}

void merchant(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* future, int* map, int* loot, int* vision, int* end, int* pos, int* floor, int* start, int* antimag) {
    printf("A strange merchant is before you.\n");
    trade(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,floor,start,antimag,1);
}

void room(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* future, int* map, int* loot, int* vision, int* end, int* pos, int* floor, int* start, int* antimag, int* checkcurse, int* nomag) {
    int control=1;
    int r=*(map+*pos);
    if (r==-1) {
        printf("There are stairs here!\n");
        return;
    }
    if (r<0) return;
    if (r>=52) hebrac(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag,0,1,0);
    else if (r%13==12) merchant(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,floor,start,antimag);
    else if (r%13==11) {
        if (r>=25) blackqueen(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag,0);
        else redqueen(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag,0,1,0);
    }
    else if (r%13==10) adventurer(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,floor,start,antimag,checkcurse,nomag,&control);
    else if (r%13==0) {
        printf("The room is empty... but maybe there is something interesting!\n");
        treasure(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag,0,1,0);
    }
    else control=combat(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,floor,start,antimag,checkcurse,nomag,r);
    if ((control==1)&&(*(map+*pos)>=0)) *(map+*pos)=-2;
}

void justadebugend(int* end){
    int i;
    printf("JUSTADEBUGEND!: Do you want to exit? [0]: No [1]: Yes\n");
    getint(&i);
    if (i==1) *end=1;
}

void exitstatus(int hpmax, int hpnow, int* aces, int* inv, int* slave, int* map, int* loot, int pos) {
    int i;
    printf("hpmax: %d; hpnow: %d\npos: %d\naces: ",hpmax,hpnow,pos);
    for (i=0; i<4; i++) printf("%d ",*(aces+i));
    printf("\ninv: ");
    for (i=0; i<INVNUM; i++) printf("%d ",*(inv+i));
    printf("\nslave: ");
    for (i=0; i<INVNUM; i++) printf("%d ",*(slave+i));
    printf("\n\nmap/loot:\n");
    for (i=0; i<12; i++) {
        printf("%d/%d ",*(map+i),*(loot+i));
        if (i%4==3) printf("\n");
    }
    printf("\n");
}


void genmap(int* future, int* map, int* loot, int* vision) {
    struct timespec a;
    a.tv_sec  = 0;
    a.tv_nsec = 1000;
    nanosleep( &a, NULL );
    struct timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);
    int i;
    for (i=0; i<12; i++) {
        if (*future>=0) {
            *(map+i)=*future;
            shiftarray(future);
        } else *(map+i)=rand()%54;
        if (*future>=0) {
            *(loot+i)=*future;
            shiftarray(future);
        } else *(loot+i)=rand()%54;
        *(vision+i)=0;
    }
}

int checkend(int* hpnow, int* aces, int deb) {
    if (*hpnow<1) return -1;
    if ((*aces)&&(*(aces+1))&&(*(aces+2))&&(*(aces+3))) return 1;
    if ((DEBUG)&&(deb==4)) return 4;
    return 0;
}

void movement(int* future, int* map, int* loot, int* vision, int* pos, int* floor, int* start, int* antimag, int* checkcurse, int free) {
    int e=-2;
    if (free==1) {
        do {
            printf("Where do you want to teleport?\n");
        } while ((e<-1)||(e>11));
        if (e>=0) {
            *pos=e;
            *start=1;
            if (*(vision+*pos)==0) *(vision+*pos)=1;
            return;
        } else {
            *floor=*floor+1;
            *antimag=0;
            *checkcurse=0;
            genmap(future,map,loot,vision);
            if (*(vision+*pos)==0) *(vision+*pos)=1;
            *start=1;
            return;
        }
    }
    printf("Where do you want to go?\n[0]: Nowhere\n");
    if (*pos-4>=0) {
        printf("[1]: North\n");
    }
    if (*pos%4) {
        printf("[4]: West\n");
    }
    if (*pos%4!=3) {
        printf("[6]: East\n");
    }
    if (*pos+4<12) {
        printf("[8]: South\n");
    }
    if (*(map+*pos)==-1) {
        printf("[-1]: Down\n");
    }
    getint(&e);
    if (e==0) return;
    if ((e==1)&&(pos-4>=0)) {
        *pos=*pos-4;
        *start=1;
        if (*(vision+*pos)==0) *(vision+*pos)=1;
        return;
    }
    if ((e==4)&&(*pos%4)) {
        *pos=*pos-1;
        *start=1;
        if (*(vision+*pos)==0) *(vision+*pos)=1;
        return;
    }
    if ((e==6)&&(*(pos)%4!=3)) {
        *pos=*pos+1;
        *start=1;
        if (*(vision+*pos)==0) *(vision+*pos)=1;
        return;
    }
    if ((e==8)&&(*pos+4<12)) {
        *pos=*pos+4;
        *start=1;
        if (*(vision+*pos)==0) *(vision+*pos)=1;
        return;
    }
    if ((e==-1)&&(*(map+*pos)==-1)) {
        *floor=*floor+1;
        *antimag=0;
        *checkcurse=0;
        genmap(future,map,loot,vision);
        *start=1;
        if (*(vision+*pos)==0) *(vision+*pos)=1;
        return;
    }
    printf("That's not an available direction!\n");
}

void useitem(int* hpmax, int* hpnow, int* inv) {
    int k;
    printf("What item do you want to use?\n");
    getint(&k);
    if ((k<0)||(k>=INVNUM)) {
        printf("You don't have that slot! Insert a number between 0 and %d!\n",INVNUM-1);
        return;
    }
    if (*(inv+k)==0) {
        printf("It's empty...\n");
        return;
    }
    if ((*(inv+k)>9)||(*hpmax==*hpnow)) {
        printf("It isn't really useful now...\n");
        return;
    }
    *hpnow=min(*hpmax,*hpnow+1+*(inv+k));
    char s[20];
    nameitem(s,*(inv+k));
    printf("You use %s!\n",s);
    *(inv+k)=0;
}

void genstairs(int* map, int* pos) {
    int i;
    int free=0;
    for (i=0; i<12; i++) {
        if (*(map+i)==-1) return;
        if (*(map+i)==-2) free++;
    }
    if (free>5) {
        *(map+*pos)=-1;
        printf("There are stairs here!\n");
    }
}

int magiccount(int* aces, int* inv) {
    int value=0;
    int i;
    for (i=0; i<INVNUM; i++) {
        if ((*(inv+i)>25)&&(*(inv+i)<35)) value+=(*(inv+i)%13)+1;
    }
    if (*(aces+2)==1) return 2*value;
    return value;
}

int magicconsume(int* aces, int* inv, int cost, char* name) {
    int value=0;
    int k;
    int a=1;
    if (*(aces+2)==1) a=2;
    int offmag[INVNUM];
    for (k=0; k<INVNUM; k++) {
        offmag[k]=0;
    }
    char s[20];
    int p=-1;
    do {
        printf("'What magic potion do you want to use?'\n");
        getint(&k);
        if ((k<0)||(k>=INVNUM)||(*(inv+k)==0)) {
            printf("Nothing here. Abort the cast?'\n[0]: No\n[1]: Yes\n");
            getint(&k);
            if (k==1) return -1;
        } else if ((*(inv+k)>35)||(*(inv+k)<26)) {
            printf("'That's not a magic potion! Abort the cast?'\n[0]: No\n[1]: Yes\n");
            getint(&k);
            if (k==1) return -1;
        } else {
            value+=(*(inv+k)%13+1)*a;
            p++;
            offmag[p]=k;
        }
        if (value<cost) printf("'You have to use (at least) %d magic potions and you are using %d potions.'\n",cost,value);
        else {
            printf("'Do you want to use %d potions:",value);
            for (k=0; k<=p; k++) {
                nameitem(s,offmag[k]);
                if (k==p) {
                    printf(" %s?\n",s);
                } else printf(" %s,",s);
            }
            k=-1;
            do {
                printf("'Do you want to cast %s?'\n[0]: No\n[1]: Yes\n",name);
                getint(&k);
                if (k==0) {
                    printf("'Abort the cast?'\n[0]: No\n[1]: Yes\n");
                    getint(&k);
                    if (k==1) return -1;
                    printf("'Do you want to use different potions?'\n[0]: No\n[1]: Yes\n");
                    if (k==0) return -1;
                    for (k=0; k<INVNUM; k++) {
                        offmag[k]=0;
                    }
                    p=-1;
                } else if (k==1) {
                    for (k=0; k<=p; k++) {
                        *(inv+offmag[k])=0;
                    }
                    return value;
                }
            } while (k<0);
        }
    } while (value<cost);
}

void remotevision(int* aces, int* inv, int* map, int* nomag) {
    char s[20];
    memset(s,0,sizeof(s));
    sprintf(s,"RemoteVision");
    int v=magicconsume(aces,inv,1,s);
    if (v<0) return;
    int k;
    int r;
    for (k=0; k<v; k++) {
        r=-1;
        do {
            printf("You can peek into any chamber. You can do this %d times.\n",v-k);
            getint(&r);
            if ((r<0)||(r>11)) r=-1;
            else {
                if (*(map+r)==-1) printf("There are stairs here.\n");
                else if (*(map+r)<=0) printf("It's empty.\n");
                else {
                    nameenemy(s,*(map+r));
                    int v=*(map+r);
                    v=v%13;
                    if ((v<1)||(v>10)) v=10;
                    else v=v+1;
                    printf("There is a %s with %d HP.\n",s,v);
                }
            }
        } while (r==-1);
    }
    if (nomag) *nomag=1;
}

void futureperception(int* aces, int* inv, int* future, int* nomag) {
    char s[20];
    memset(s,0,sizeof(s));
    sprintf(s,"FuturePerception");
    int v=magicconsume(aces,inv,1,s);
    if (v<0) return;
    int i;
    v=min(v,INVNUM);
    printf("Your future is: ");
    for (i=0; i<v; i++) {
        if (*(future+i)<0) *(future+i)=rand()%54;
        if (*(future+i)>51) printf("H");
        else if (*(future+i)%13==12) printf("K");
        else if (*(future+i)%13==11) printf("Q");
        else if (*(future+i)%13==10) printf("J");
        else printf("%d",*(future+i)%13+1);
        if (i+1==v) printf(".\n");
        else printf(", ");
    }
    if (nomag) *nomag=1;
}

void healing(int* hpmax, int* hpnow, int* aces, int* inv, int* nomag) {
    char s[20];
    memset(s,0,sizeof(s));
    sprintf(s,"Healing");
    int v=magicconsume(aces,inv,2,s);
    if (v<0) return;
    *hpnow=min(*hpmax,*hpnow+(v/2));
    printf("You heal yourself for %d HP and your current HP are &d!\n",v/2,*hpnow);
    if (nomag) *nomag=1;
}

void escape(int* aces, int* inv, int* future, int* map, int* loot, int* vision, int* pos, int* floor, int* start, int* control, int* antimag, int* checkcurse) {
    char s[20];
    memset(s,0,sizeof(s));
    sprintf(s,"Escape");
    int v=magicconsume(aces,inv,3,s);
    if (v<0) return;
    *control=0;
    movement(future,map,loot,vision,pos,floor,start,antimag,checkcurse,0);
    printf("You escaped!\n");
}

void paralysis(int* aces, int* inv, int* contator, int* modenemy, int* nomag) {
    char s[20];
    memset(s,0,sizeof(s));
    sprintf(s,"Paralysis");
    int v=magicconsume(aces,inv,4,s);
    if (v<0) return;
    *contator=2;
    *modenemy=0;
    printf("You paralyse your enemy!\n");
    if (nomag) *nomag=1;
}

void doubleattack(int* aces, int* inv, int* datt, int* nomag) {
    char s[20];
    memset(s,0,sizeof(s));
    sprintf(s,"DoubleAttack");
    int v=magicconsume(aces,inv,4,s);
    if (v<0) return;
    *datt=1;
    printf("You will perform a double attack!\n");
    if (nomag) *nomag=1;
}

void superstrength(int* aces, int* inv, int* modatt, int* nomag) {
    char s[20];
    memset(s,0,sizeof(s));
    sprintf(s,"SuperStrength");
    int v=magicconsume(aces,inv,5,s);
    if (v<0) return;
    *modatt=2;
    printf("You will hit harder!\n");
    if (nomag) *nomag=1;
}

void antimagic(int* aces, int* inv, int* antimag, int* nomag) {
    char s[20];
    memset(s,0,sizeof(s));
    sprintf(s,"AntiMagic");
    int v=magicconsume(aces,inv,5,s);
    if (v<0) return;
    *antimag=1;
    printf("This floor is embedded in an antimagic field!\n");
    if (nomag) *nomag=1;
}

void stealingspirit(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* future, int* map, int* loot, int* vision, int* end, int* pos, int* floor, int* start, int* antimag, int* checkcurse, char* st, int* control) {
    char s[20];
    memset(s,0,sizeof(s));
    sprintf(s,"StealingSpirit");
    int v=magicconsume(aces,inv,6,s);
    if (v<0) return;
    printf("Before your escape, you steal the %s's property!\n",st);
    treasure(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag,0,1,1);
    *control=0;
    movement(future,map,loot,vision,pos,floor,start,antimag,checkcurse,0);
}

void extendednameenemy(char* s, int enemy) {
    memset(s,0,sizeof(s));
    if (enemy%13==10) sprintf(s,"adventurer with 10 HP");
    else if (enemy>51) sprintf(s,"Hebrac itself");
    else if (enemy%13==0) sprintf(s,"...nothing");
    else if ((enemy%13==11)&&(enemy<26)) sprintf(s,"white priestess");
    else if ((enemy%13==11)&&(enemy>26)) sprintf(s,"black priestess");
    else if (enemy%13==12) sprintf(s,"merchant");
    else if (enemy<13) sprintf(s,"amazon with %d HP",enemy%13);
    else if (enemy<26) sprintf(s,"demon with %d HP",enemy%13);
    else if (enemy<39) sprintf(s,"magician with %d HP",enemy%13);
    else sprintf(s,"warrior with %d HP",enemy%13);
}

void bodyswitch(int* aces, int* inv, int* future, int* map, int* pos, int* start, int* control, int* nomag) {
    struct timespec a;
    a.tv_sec  = 0;
    a.tv_nsec = 1000;
    nanosleep( &a, NULL );
    struct timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);
    char s[30];
    memset(s,0,sizeof(s));
    sprintf(s,"StealingSpirit");
    int v=magicconsume(aces,inv,7,s);
    if (v<0) return;
    v=-1;
    do {
        printf("What enemy you want to transmute?\n");
        getint(&v);
    } while ((v<0)||(v>11));
    if (*(map+v)>0) {
        int c;
        if (*future>=0) {
            c=*future;
            shiftarray(future);
        } else c=rand()%54;
        extendednameenemy(s,c);
        printf("The enemy is transmuted into a %s!\n",s);
        *(map+v)=c;
        if (v==*pos) {
            *start=1;
            *control=0;
        }
    } else printf("Nothing here...\n");
    if (nomag) *nomag=2;
}

void teleport(int* aces, int* inv, int* future, int* map, int* loot, int* vision, int* pos, int* floor, int* start, int* control, int* antimag, int* checkcurse, int combat) {
    char s[20];
    memset(s,0,sizeof(s));
    sprintf(s,"Teleport");
    int v=magicconsume(aces,inv,8,s);
    if (v<0) return;
    if (combat==1) {
        *control=0;
    }
    movement(future,map,loot,vision,pos,floor,start,antimag,checkcurse,1);
    printf("You teleported to the desired location!\n");
}

void revelation(int* aces, int* inv, int* vision, int* nomag) {
    char s[20];
    memset(s,0,sizeof(s));
    sprintf(s,"Revelation");
    int v=magicconsume(aces,inv,9,s);
    if (v<0) return;
    for (v=0; v<12; v++) {
        if (*(vision+v)==0) *(vision+v)=1;
    }
    if (nomag) *nomag=1;
    printf("You know something of this floor!\n");
    if (nomag) *nomag=1;
}

void hellbomb(int* aces, int* inv, int* map, int* pos, int combat, int* start, int* nomag) {
    char s[20];
    memset(s,0,sizeof(s));
    sprintf(s,"HellBomb");
    int v=magicconsume(aces,inv,9,s);
    if (v<0) return;
    if (combat==1) *start=1;
    if ((*pos-4>=0)&&(*(map+*pos-4)>0)) *(map+*pos-4)=0;
    if ((*pos%4)&&(*(map+*pos-1)>0)) *(map+*pos-1)=0;
    if ((*pos%4!=3)&&(*(map+*pos+1)>0)) *(map+*pos+1)=0;
    if ((*pos+4<12)&&(*(map+*pos+4)>0)) *(map+*pos+4)=0;
    if (*(map+*pos)>0) *(map+*pos)=0;
    printf("You obliterate the enemies near you with fire!\n");
    if (nomag) *nomag=1;
}

void curse(int* aces, int* inv, int* checkcurse, int* nomag) {
    char s[20];
    memset(s,0,sizeof(s));
    sprintf(s,"Curse");
    int v=magicconsume(aces,inv,10,s);
    if (v<0) return;
    *checkcurse=1;
    printf("You curse the enemies on this floor! They are sick now!\n");
    if (nomag) *nomag=1;
}

void genieofluck(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* future, int* map, int* loot, int* vision, int* end, int* pos, int* antimag, int combat, int* nomag) {
    char s[20];
    memset(s,0,sizeof(s));
    sprintf(s,"GenieofLuck");
    int v=magicconsume(aces,inv,11,s);
    if (v<0) return;
    printf("You evoke a djinn of Luck and he gives you five gift!\n");
    treasure(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag,1,0,combat);
    treasure(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag,1,0,combat);
    treasure(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag,1,0,combat);
    treasure(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag,1,0,combat);
    treasure(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag,1,0,combat);
    if (nomag) *nomag=1;
}

void stonestatue(int*aces, int* inv, int* map, int times, int combat, int free) {
    if (combat==1) {
        printf("Nope.\n");
        return;
    }
    int v;
    if (free==0) {
        char s[20];
        memset(s,0,sizeof(s));
        sprintf(s,"StoneStatue");
        v=magicconsume(aces,inv,15,s);
        if (v<0) return;
    }
    int e;
    for (v=0; v<times; v++) {
        e=-1;
        do {
            printf("You can turn an enemy in a stone statue. You can do this %d times. What enemy do you want to kill?\n",times-v);
            getint(&e);
        } while ((e<0)||(e>11));
        if (*(map+e)>0) *(map+e)=0;
    }
}

void godvision(int* aces, int* inv, int* vision, int* nomag, int free) {
    int v;
    if (free==1) {
        for (v=0; v<12; v++) *(vision+v)=2;
        return;
    }
    char s[20];
    memset(s,0,sizeof(s));
    sprintf(s,"GodVision");
    v=magicconsume(aces,inv,15,s);
    if (v<0) return;
    for (v=0; v<12; v++) *(vision+v)=2;
    printf("You know something this floor perfectly!\n");
    if (nomag) *nomag=1;
}

void magic(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* future, int* map, int* loot, int* vision, int* end, int* pos, int* floor, int* start, int* antimag, int* checkcurse, int combat, int* control, int* contator, int* modenemy, int* datt, int* modatt, int* nomag, char* s) {
    int v=magiccount(aces,inv);
    int k;
    if ((nomag)&&(*nomag==1)) {
        printf("You are exausted and can't do magic.\n");
        return;
    }
    if (v==0) {
        printf("You don't have magic potions.\n");
        return;
    }
    if (v>=1) printf("What spell do you want to cast?\n[0]: Nothing\n[1]: RemoteVision\n[2]: FuturePerception\n");
    if (v>=2) printf("[3]: Healing\n");
    if ((v>=3)&&(combat==1)) printf("[4]: Escape\n");
    if (v>=4) {
        if (combat==1) printf("[5]: Paralysis\n[6]: DoubleAttack\n");
    }
    if (v>=5) {
        if (combat==1) printf("[7]: SuperStrength\n");
        printf("[8]: AntiMagic\n");
    }
    if ((v>=6)&&(combat==1)) printf("[9]: StealingSpirit\n");
    if (v>=7) printf("[10]: BodySwitch\n");
    if (v>=8) printf("[11]: Teleport\n");
    if (v>=9) printf("[12]: Revelation\n[13]: HellBomb\n");
    if (v>=10) printf("[14]: Curse\n");
    if (v>=11) printf("[15]: GenieofLuck\n");
    if (v>=15) printf("[16]: StoneStatue\n[17]: GodVision\n");
    getint(&k);
    if (k==0) return;
    if ((k==1)&&(v>=1)) remotevision(aces,inv,map,nomag);
    else if ((k==2)&&(v>=1)) futureperception(aces,inv,future,nomag);
    else if ((k==3)&&(v>=2)) healing(hpmax,hpnow,aces,inv,nomag);
    else if ((k==4)&&(v>=3)&&(combat==1)) escape(aces,inv,future,map,loot,vision,pos,floor,start,control,antimag,checkcurse);
    else if ((k==5)&&(v>=4)&&(combat==1)) paralysis(aces,inv,contator,modenemy,nomag);
    else if ((k==6)&&(v>=4)&&(combat==1)) doubleattack(aces,inv,datt,nomag);
    else if ((k==7)&&(v>=5)&&(combat==1)) superstrength(aces,inv,modatt,nomag);
    else if ((k==8)&&(v>=5)) antimagic(aces,inv,antimag,nomag);
    else if ((k==9)&&(v>=6)&&(combat==1)) stealingspirit(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,floor,start,antimag,checkcurse,s,control);
    else if ((k==10)&&(v>=7)) bodyswitch(aces,inv,future,map,pos,start,control,nomag);
    else if ((k==11)&&(v>=8)) teleport(aces,inv,future,map,loot,vision,pos,floor,start,control,antimag,checkcurse,combat);
    else if ((k==12)&&(v>=9)) revelation(aces,inv,vision,nomag);
    else if ((k==13)&&(v>=9)) hellbomb(aces,inv,map,pos,combat,start,nomag);
    else if ((k==14)&&(v>=10)) curse(aces,inv,checkcurse,nomag);
    else if ((k==15)&&(v>=11)) genieofluck(hpmax,hpnow,aces,inv,slave,future,map,loot,vision,end,pos,antimag,combat,nomag);
    else if ((k==16)&&(v>=15)) stonestatue(aces,inv,map,6,combat,0);
    else if ((k==17)&&(v>=15)) godvision(aces,inv,vision,nomag,0);
    else printf("You can't do that!\n");
}

void clear() {
    if ((OS==0)||(OS==2)) system("clear");
    if (OS==1) system("cls");
}

void suit(int i) {
    if (i==0) printf("♡");
    if (i==1) printf("♢");
    if (i==2) printf("♣");
    if (i==3) printf("♠");
}

void printroom(int* map, int* tre, int* vis, int pos, int here) {
    if (*(vis+pos)==0) {
        printf(" ?  :  ? ");
        return;
    }
    if (*(map+pos)==-1) printf(" < ");
    else if (*(map+pos)==-2) printf(" ø ");
    else if (*(map+pos)>51) printf(" H ");
    else if (*(map+pos)%13==0) printf("   ");
    else if (*(map+pos)%13==9) {
        printf("10");
        suit(*(map+pos)/13);
    }
    else if (*(map+pos)%13==10) printf(" U ");
    else if (*(map+pos)%13==11) {
        printf(" P");
        suit(*(map+pos)/13);
    }
    else if (*(map+pos)%13==12) printf(" M ");
    else {
        printf(" %d",*(map+pos)%13+1);
        suit(*(map+pos)/13);
    }
    if (here==0) printf(" : ");
    else printf(" @ ");
    if (*(vis+pos)==1) {
        printf(" ? ");
        return;
    }
    if (*(tre+pos)==-1) printf(" ø ");
    else if (*(tre+pos)>51) printf(" H ");
    else if (*(tre+pos)%13==0) {
        printf(" ☼");
        suit(*(tre+pos)/13);
    }
    else if (*(tre+pos)%13==9) {
        printf("10");
        suit(*(tre+pos)/13);
    }
    else if (*(tre+pos)%13==10) printf(" U ");
    else if (*(tre+pos)%13==11) {
        printf(" P");
        suit(*(tre+pos)/13);
    }
    else if (*(tre+pos)%13==12) {
        printf(" J");
        suit(*(tre+pos)/13);
    }
    else {
        printf(" %d",*(tre+pos)%13+1);
        suit(*(tre+pos)/13);
    }
}

void printmap(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* map, int* tre, int* vis, int* pos) {
    clear();
    int i;
    char s[10];
    printf("╔══════════╦══════════╦══════════╦══════════╗\n");
    printf("║          ║          ║          ║          ║\n");
    printf("║");
    int here=0;
    for (i=0; i<12; i++) {
        if ((i%4==0)&&(i>0)) {
            printf("\n║          ║          ║          ║          ║\n");
            printf("╠══════════╬══════════╬══════════╬══════════╣\n");
            printf("║          ║          ║          ║          ║\n");
            printf("║");
        }
        if (i==*pos) here=1;
        printroom(map,tre,vis,i,here);
        printf(" ║");
        here=0;
    }
    printf("\n║          ║          ║          ║          ║\n");
    printf("╚══════════╩══════════╩══════════╩══════════╝\n");
    printf("HP %d/%d\t",*hpnow,*hpmax);
    for (i=0; i<4; i++) {
        if (*(aces+i)==1) suit(i);
        else printf(" ");
        printf(" ");
    }
    printf("\nCompanions: %d\tInventory: ",numslav(slave));
    for (i=0; i<INVNUM; i++) {
        if (*(inv+i)==0) printf("E");
        else {
            printf("%d",*(inv+i)%13+1);
            suit(*(inv+i)/13);
        }
        printf(" ");
    }
    printf("\n");
}

//fare un parser per una migliore gestione dei comandi

//una funzione per salvare?

//ora bisogna capire dove e quando far aggiornare la mappa o ulteriori interfacce
//fare una specie di stream di tot righe fissate dopo la mappa, e aggiornare più spesso

//perchè diamine slave è un array e non un int qualsiasi???

int main(){
    struct timespec a;
    a.tv_sec  = 0;
    a.tv_nsec = 1000;
    nanosleep( &a, NULL );
    struct timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);
    printf("\t\t\t\tWelcome to\n");
    printf("\t\t╦ ╦┌─┐┌┐ ┬─┐┌─┐┌─┐'┌─┐  ╔╦╗┬ ┬┌┐┌┌─┐┌─┐┌─┐┌┐┌\n");
    printf("\t\t╠═╣├┤ ├┴┐├┬┘├─┤│   └─┐   ║║│ │││││ ┬├┤ │ ││││\n");
    printf("\t\t╩ ╩└─┘└─┘┴└─┴ ┴└─┘ └─┘  ═╩╝└─┘┘└┘└─┘└─┘└─┘┘└┘\n");
    printf("\t\t                   VANILLA\n");
    int hpmax=15, hpnow=15;
    int aces[4]={0,0,0,0};
    int inv[INVNUM]; //no limitations?; dynamic arrays?
    int slave[INVNUM]; //no limitations?; dynamic arrays?
    int future[INVNUM]; //no limitations?; dynamic arrays?
    int start;
    for (start=0; start<INVNUM; start++) {
        inv[start]=0;
        slave[start]=0;
        future[start]=-1;
    }
    int map[12],loot[12],vision[12];
    genmap(future,map,loot,vision);
    int floor=1, end=0, antimag=0, checkcurse=0;
    int pos=2;
    int k;
    do {
        printf("Where do you want to enter?\n[1]: Northwest\n[3]: Northeast\n[7]: Southwest\n[9]: Southeast\n");
        getint(&start);
        if (start==1) pos=0;
        else if (start==3) pos=3;
        else if (start==7) pos=8;
        else if (start==9) pos=11;
        else {
            pos=1;
            printf("You lost one day to decide where to enter!\n");
        }
    } while (pos==1);
    vision[pos]=1;
    start=1;
    int nomag=0;
    do {
        if (start==1) {
            printmap(&hpmax,&hpnow,aces,inv,slave,map,loot,vision,&pos);
            start=0;
            room(&hpmax,&hpnow,aces,inv,slave,future,map,loot,vision,&end,&pos,&floor,&start,&antimag,&checkcurse,&nomag);
        }
        end=checkend(&hpnow,aces,k);
        if ((end==0)&&(start==0)) {
            genstairs(map,&pos);
            printf("What do you want to do?\n[0]: Movement\n[1]: Magic\n[2]: Item\n");
            if (*(loot+pos)>0) printf("[3]: Treasure\n");
            if (DEBUG) printf("[4]: EXIT\n");
            getint(&k);
            if (k==0) movement(future,map,loot,vision,&pos,&floor,&start,&antimag,&checkcurse,0);
            else if (k==1) magic(&hpmax,&hpnow,aces,inv,slave,future,map,loot,vision,&end,&pos,&floor,&start,&antimag,&checkcurse,0,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
            else if (k==2) useitem(&hpmax,&hpnow,inv);
            else if ((k==3)&&(*(loot+pos)>0)) treasure(&hpmax,&hpnow,aces,inv,slave,future,map,loot,vision,&end,&pos,&antimag,0,1,0);
            else if ((k==4)&&(DEBUG)) justadebugend(&end);
            else printf("What?\n");
        }
        end=checkend(&hpnow,aces,k);
    } while (end==0);
    if (DEBUG) exitstatus(hpmax,hpnow,aces,inv,slave,map,loot,pos);
    if (end==1) printf("You win! Maybe I will find a better endscreen :P\n");
    else printf("You lose!\n");
}
