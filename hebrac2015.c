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

#define INVNUM 10
#define DEBUG 1

//fare ifdef per capire il sistema operativo

void treasure(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* map, int* loot, int* end, int* pos, int rec, int stat);

void magic(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* map, int* loot, int* end, int* pos, int combat);

void hebrac(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* map, int* loot, int* end, int* pos, int rec) {
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
        scanf("%d",&r);
        if ((r!=0)&&(r!=1)&&(r!=2)) {
            if (i==0) {
                printf("'I don't have all the day...'\n");
                i=1;
            } else if (i>0) {
                printf("'Don't be rude the next time!'\nHebrac disappears!\n");
                *(loot+*pos)=-1;
                return;
            }
        }
    } while ((r!=0)&&(r!=1)&&(r!=2));
    printf("'As you wish...'\n");
    if (r==0) {
        printf("Hebrac disappears!\n");
        *(loot+*pos)=-1;
        return;
    }
    i=rand()%2;
    if (i==0) {
        if (r==1) printf("Tails! You lose 5 HP!\nHebrac disappears!\n");
        else printf("Heads! You lose 5 HP!\nHebrac disappears!\n");
        *(loot+*pos)=-1;
        *hpnow=*hpnow-5;
        return;
    } else {
        if (r==1) printf("Heads! You can take the treasure!\nHebrac disappears!\n");
        else printf("Tails! You can take the treasure!\nHebrac disappears!\n");
        treasure(hpmax,hpnow,aces,inv,slave,map,loot,end,pos,rec,0);
    }
}

void genie(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* map, int* loot, int* end, int* pos, int r) {
    if (r==12) {
        printf("You rub the lantern! From the smoke, a djinn of Life appears!\nYour maximum HP are increased by 2!\n");
        *hpmax=*hpmax+2;
        return;
    }
    if (r==25) {
        printf("You rub the lantern! From the smoke, a djinn of Luck appears!\nYou find some treasure!\n");
        treasure(hpmax,hpnow,aces,inv,slave,map,loot,end,pos,1,0);
        treasure(hpmax,hpnow,aces,inv,slave,map,loot,end,pos,1,0);
        treasure(hpmax,hpnow,aces,inv,slave,map,loot,end,pos,1,0);
        return;
    }
    if (r==38) {
        printf("You rub the lantern! From the smoke, a djinn of Destiny appears!\nNow you know this floor perfectly!\n");
        //godvision(); da inserire quando ci sono le spell
        return;
    }
    printf("You rub the lantern! From the smoke, a djinn of Death appears!\nYou can choose to kill 3 enemies!\n");
    //stonestatue(map,3); da inserire quando ci sono le spell
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
            if ((*(inv+pos)>0)&&(*(inv+pos)%13!=10)) min=pos;
        }
        else if ((*(inv+pos)%13!=10)&&(value(*inv+min)>value(*inv+pos))) min=pos;
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
    if (i==12) {
        sprintf(s,"djinn of Destiny");
        return;
    }
    if (i==12) {
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

void removeleast(int* aces, int* inv) {
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
            return;
        }
        if (*(aces+1)==1) {
            *(aces+1)=0;
            printf("'I'm sorry, but I have to take your Bag of Meres.'\nThe black priestess disappears!\n");
            return;
        }
    }
    int p=leastvalueinv(inv);
    if (p<=0) {
        ("'I can't take anything from you!'\nThe black priestess disappears!\n");
        return;
    }
    char s[20];
    nameitem(s,*(inv+p));
    printf("'I'm sorry, but I have to take your %s .'\nThe black priestess disappears!\n",s);
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

void removemost(int* aces, int* inv) {
    if (checkpositiveace(aces)) {
        if (*(aces+1)==1) {
            *(aces+1)=0;
            printf("'Nice, I will take your Bag of Meres.'\nThe black priestess disappears!\n");
            return;
        }
        if (*(aces)==1) {
            *(aces)=0;
            printf("'Nice, I will take your Ruby of Gaza.'\nThe black priestess disappears!\n");
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
    if (p<=0) {
        ("'I can't take anything from you!'\nThe black priestess disappears!\n");
        return;
    }
    char s[20];
    nameitem(s,*(inv+p));
    printf("'Not bad, I will take your %s.'\nThe black priestess disappears!\n",s);
    *(inv+p)=0;
}

void blackqueen(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* map, int* loot, int* end, int* pos, int good) {
    if (good==1) {
        printf("It is a black priestess, a kleptomaniac demon!\n'Because you freed me, I will take your cheapest item with my black magic...'\n");
        removeleast(aces,inv);
        return;
    }
    printf("It is a black priestess, a kleptomaniac demon!\n'Ah, I will take something expensive from you!'\n");
    removemost(aces,inv);
    treasure(hpmax,hpnow,aces,inv,slave,map,loot,end,pos,0,1);
}

void redqueen(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* map, int* loot, int* end, int* pos, int rec, int stat) {
    int i;
    printf("You meet a white priestess, a gentle pixie!\n'Greetings! I want to help you, but you don't have to be greedy. Do you want a gift or you want to be healed?'\n[0]: Gift\n[1]: Heal\n");
    do {
        scanf("%d",&i);
        if (i==0) {
            printf("'As you wish, here your gift!'\nThe white priestess disappears!\n");
            treasure(hpmax,hpnow,aces,inv,slave,map,loot,end,pos,rec,stat);
            return;
        }
        if (i==1) {
            printf("'As you wish, I will heal you!'\nThe white priestess disappears!\n");
            *hpnow=*hpmax;
            *(loot+*pos)=-1;
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

void addaces(int* aces, int a) {
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
    if (a=0) printf("You found the Ruby of Gaza!\n");
    else if (a=1) printf("You found the Bag of Meres!\n");
    else if (a=2) printf("You found the Scepter of Leynos!\n");
    else printf("You found the Bracelet of Armok!\n");
}

void dropinv(int* inv, int r) {
    int i;
    char s[20];
    char t[20];
    nameitem(s,r);
    printf("Your bag is full! Do you want to drop something to keep %s?\n[0]: No\n[1]: Yes\n",s);
    scanf("%d",&i);
    if (i==0) {
        printf("You don't keep the %s.\n",s);
    } else {
        i=0;
        do {
            printf("What do you want to drop?\n");
            scanf("%d",&i);
            if ((i<0)||(i>=INVNUM)) {
                printf("You don't have that slot! Insert a number between 0 and %d!\n",INVNUM-1);
                i=0;
            } else {
                int k;
                nameitem(t,*(inv+i));
                printf("Do you want to drop the %s?\n[0]: No\n[1]: Yes\n",t);
                scanf("%d",&k);
                if (k==1) {
                    printf("You dropped the %s to keep the %s.\n",s,t);
                    *(inv+i)=r;
                    i=-1;
                } else if (k!=0) {
                    printf("You don't have all the day to decide...\n");
                }
            }
        } while (i!=-1);
    }
}

void treasure(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* map, int* loot, int* end, int* pos, int rec, int stat) {
    struct timespec a;
    a.tv_sec  = 0;
    a.tv_nsec = 1000;
    nanosleep( &a, NULL );
    struct timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);
    int r,n;
    if (stat==0) r=rand()%54;
    else r=*(loot+*pos);
    if (r==-1) {
        printf("This room is empty...\n");
        return;
    }
    if (stat==1) {
        printf("Do you want to take the treasure in this room?\n[0]: No\n[1]: Yes\n");
        scanf("%d",&n);
        if (n==0) return;
    }
    if (r>=52) hebrac(hpmax,hpnow,aces,inv,slave,map,loot,end,pos,rec);
    else if (r%13==12) {
        if (rec==0) genie(hpmax,hpnow,aces,inv,slave,map,loot,end,pos,0);
        else printf("An empty lantern...");
    }
    else if (r%13==11) {
    if (r>=25) blackqueen(hpmax,hpnow,aces,inv,slave,map,loot,end,pos,1);
    else redqueen(hpmax,hpnow,aces,inv,slave,map,loot,end,pos,rec,0);
    }
    else if (r%13==10) addslave(slave);
    else if (r%13==0) addaces(aces,r);
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
    if (stat==1) *(loot+*pos)=-1;
}

int valueitem(int n) {
    if (n>51) return 2;
    if (n%13==0) return 12;
    if (n%13==10) return 8;
    if (n%13==11) return 9;
    if (n%13==12) return 10;
    if ((n>25)&&(n<39)) return 2*(n%13);
    return n%13;
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

void goodsoffer(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* map, int* loot, int* end, int* pos) {
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
        scanf("%d",&k);
        if (k==0) {
            printf("'What item do you want to offer?'\n");
            scanf("%d",&k);
            if ((k<0)||(k>=INVNUM)||(*(inv+k)==0)) {
                printf("'Are you kidding me? Do you want to abort the trade?'\n[0]: No\n[1]: Yes\n");
                scanf("%d",&k);
                if (k==1) return;
            } else {
                value+=valueitem(*(inv+k));
                p++;
                offitem[p]=k;
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
            scanf("%d",&k);
            if (k==1) return;
        }
        if (value<valueitem(*(loot+*pos))) printf("'My item is valued %d gems and you offer is worth %d gems.'\n",valueitem(*(loot+*pos)),value);
        else {
            printf("'I'm satisfied with your offer of %d slaves and ",offslav);
            for (k=0; k<=p; k++) {
                nameitem(s,offitem[k]);
                printf("%s",s);
            }
            if (p<0) printf("nothing else.'\n");
            else printf(".'\n");
            k=-1;
            do {
                printf("'Do you accept the trade?'\n[0]: No\n[1]: Yes");
                scanf("%d",&k);
                if (k==0) {
                    printf("'Do you want to abort the trade?'\n[0]: No\n[1]: Yes\n");
                    scanf("%d",&k);
                    if (k==1) return;
                    printf("'Do you want to propose another offer?'\n[0]: No\n[1]: Yes\n");
                    if (k==0) return;
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
                    treasure(hpmax,hpnow,aces,inv,slave,map,loot,end,pos,0,1);
                }
            } while (k<0);
        }
    } while (value<valueitem(*(loot+*pos)));
}

void gemoffer(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* map, int* loot, int* end, int* pos) {
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
        scanf("%d",&k);
        if ((k<0)||(k>=INVNUM)||(*(inv+k)==0)) {
            printf("'Are you kidding me? Do you want to abort the trade?'\n[0]: No\n[1]: Yes\n");
            scanf("%d",&k);
            if (k==1) return;
        } else if ((*(inv+k)>22)||(*(inv+k)<14)) {
            printf("'That's not a gem! Do you want to abort the trade?'\n[0]: No\n[1]: Yes\n");
            scanf("%d",&k);
            if (k==1) return;
        } else {
            value+=*(inv+k)%13;
            p++;
            offgem[p]=k;
        }
        if (value<valueitem(*(loot+*pos))) printf("'My item is valued %d gems and you offer is worth %d gems.'\n",valueitem(*(loot+*pos)),value);
        else {
            printf("'I'm satisfied with your offer of %d gems:",value);
            for (k=0; k<=p; k++) {
                nameitem(s,offgem[k]);
                if (k==p) {
                    printf(" %s gems.'\n",s);
                } else printf(" %s gems,",s);
            }
            k=-1;
            do {
                printf("'Do you accept the trade?'\n[0]: No\n[1]: Yes");
                scanf("%d",&k);
                if (k==0) {
                    printf("'Do you want to abort the trade?'\n[0]: No\n[1]: Yes\n");
                    scanf("%d",&k);
                    if (k==1) return;
                    printf("'Do you want to propose another offer?'\n[0]: No\n[1]: Yes\n");
                    if (k==0) return;
                    for (k=0; k<INVNUM; k++) {
                        offgem[k]=0;
                    }
                    p=-1;
                } else if (k==1) {
                    for (k=0; k<=p; k++) {
                        *(inv+offgem[k])=0;
                    }
                    treasure(hpmax,hpnow,aces,inv,slave,map,loot,end,pos,0,1);
                }
            } while (k<0);
        }
    } while (value<valueitem(*(loot+*pos)));
}

void exchange(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* map, int* loot, int* end, int* pos, int type) {
    char s[20];
    nameitem(s,*(loot+*pos));
    if (*(aces+1)==1) {
        printf("You put out enough gems from your bag of Meres and buy the %s.\n",s);
        if (*(loot+*pos)==0) {
            *(aces)=1;
            return;
        }
        if (*(loot+*pos)==26) {
            *(aces+2)=1;
            return;
        }
        if (*(loot+*pos)==39) {
            *(aces+3)=1;
            return;
        }
        else if (*(loot+*pos)%13==10) {
            addslave(slave);
            return;
        }
        else if (*(loot+*pos)%13==11) {
            redqueen(hpmax,hpnow,aces,inv,slave,map,loot,end,pos,0,0);
            return;
        }
        else if (*(loot+*pos)%13==12) {
            genie(hpmax,hpnow,aces,inv,slave,map,loot,end,pos,*(loot+*pos));
            return;
        }
        else {
            treasure(hpmax,hpnow,aces,inv,slave,map,loot,end,pos,0,1);
            return;
        }
    }
    if (valueitem(*(loot+*pos))>valueinv(inv,slave)) {
        printf("'You don't have enough goods to trade!'\n");
        *(loot+*pos)=-1;
        return;
    }
    if ((type==1)&&(valueitem(*(loot+*pos))>gemcount(inv))) {
        printf("'You don't have enough gems to trade!'\n");
        *(loot+*pos)=-1;
        return;
    }
    if (type==0) {
        goodsoffer(hpmax,hpnow,aces,inv,slave,map,loot,end,pos);
        return;
    }
    gemoffer(hpmax,hpnow,aces,inv,slave,map,loot,end,pos);
}

void trade(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* map, int* loot, int* end, int* pos, int type) {
    if ((type==1)&&(*(loot+*pos)>13)&&(*(loot+*pos)<23)) {
        printf("'I'm sorry, but I have already sold my goods.'\n");
        *(loot+*pos)=-1;
        return;
    }
    if ((type==0)&&(*(loot+*pos)%13==0)) {
        printf("'I'm sorry, but I don't want to trade my artifact.'\n");
        *(loot+*pos)=-1;
        return;
    }
    if ((*(loot+*pos)%13==11)&&(*(loot+*pos)>25)) {
        printf("'I don't think you are interest in a black priestess...'\n");
        *(loot+*pos)=-1;
        return;
    }
    int i;
    char s[20];
    nameitem(s,*(loot+*pos));
    do {
        printf("'Are you interested in my %s?'\n",s);
        if (*(loot+*pos)%13==0) {
            if (((*(loot+*pos)==0)&&(*aces==1))||((*(loot+*pos)==13)&&(*(aces+1)==1))||((*(loot+*pos)==26)&&(*(aces+2)==1))||((*(loot+*pos)==39)&&(*(aces+3)==1))) {
                printf("You see it's only a pathetic imitation...\n");
                return;
            }
        }
        printf("[0]: No\n[1]: Yes\n");
        scanf("%d",&i);
        if (i==0) {
            *(loot+*pos)=-1;
            return;
        }
        if (i==1) {
            exchange(hpmax,hpnow,aces,inv,slave,map,loot,end,pos,type);
            *(loot+*pos)=-1;
            return;
        }
        else {
            i=-1;
            printf("'What?'\n");
        }
    } while (i=-1);
}

int hit() {
    struct timespec a;
    a.tv_sec  = 0;
    a.tv_nsec = 1000;
    nanosleep( &a, NULL );
    struct timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);
    int k=rand()%13;
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
    scanf("%d",&k);
    if (k==0) {
        printf("What item do you want to use?\n");
        scanf("%d",&k);
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
    } else printf("Maybe you are a little too much excited for this fight!\n");
}

void combat(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* map, int* loot, int* end, int* pos, int enemy) {
    char s[10];
    nameenemy(s,enemy);
    int hpenemy=enemy%13+1;
    if (enemy==0) hpenemy=10;
    printf("An enemy %s appears! It has %d HP!\n",s,hpenemy);
    int e=0;
    int k;
    int bonusnext=0;
    int bonuscomb=0;
    int bonusaces=0;
    if (*(aces+3)) bonusaces=3;
    do {
        printf("What do you want to do?\n[0]: Attack\n[1]: Magic\n[2]: Items\n");
        scanf("%d",&k);
        if (k==0) {
            k=hit()+bonusnext+bonuscomb+bonusaces;
            hpenemy-=k;
            hpenemy=max(hpenemy,0);
            printf("You strike the %s for %d damage! It has %d HP!\n",s,k,hpenemy);
            if (hpenemy==0) {
                e=1;
                treasure(hpmax,hpnow,aces,inv,slave,map,loot,end,pos,0,1);
            }
            else {
                k=hit();
                *hpnow=*hpnow-k;
                *hpnow=max(*hpnow,0);
                printf("The %s strikes you for %d damage! You have %d HP!\n",s,k,*hpnow);
                if (*hpnow<=0) e=1;
            }
        } else if (k==1) {
            //implementare la magia, qui si è in combat
        } else if (k==2) {
            useitemcombat(hpmax,hpnow,inv,slave,&bonusnext,&bonuscomb);
        } else {
            printf("What do you want to do?! It is really an uneasy moment...\n");
        }
    } while (e==0);
}

void adventurer(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* map, int* loot, int* end, int* pos) {
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
    if (i==0) printf("her ");
    else printf("him ");
    printf("or you want to trade something?\n[0]: Battle\n[1]: Trade\n");
    do {
        scanf("%d",&i);
        if (i==0) combat(hpmax,hpnow,aces,inv,slave,map,loot,end,pos,10);
        else if (i==1) trade(hpmax,hpnow,aces,inv,slave,map,loot,end,pos,0);
        else {
            printf("The adventurer didn't understand your intentions! Do you want to battle or to trade?\n[0]: Battle\n[1]: Trade\n");
            i=-1;
        }
    } while ((i!=0)&&(i!=1));
}

void merchant(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* map, int* loot, int* end, int* pos) {
    printf("A strange merchant is before you.\n");
    trade(hpmax,hpnow,aces,inv,slave,map,loot,end,pos,1);
}

void room(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* map, int* loot, int* end, int* pos) {
    int r=*(map+*pos);
    if (r==-1) {
        printf("There are stairs here!\n");
        return;
    }
    if (r<0) return;
    if (r>=52) hebrac(hpmax,hpnow,aces,inv,slave,map,loot,end,pos,0);
    else if (r%13==12) merchant(hpmax,hpnow,aces,inv,slave,map,loot,end,pos);
    else if (r%13==11) {
        if (r>=25) blackqueen(hpmax,hpnow,aces,inv,slave,map,loot,end,pos,0);
        else redqueen(hpmax,hpnow,aces,inv,slave,map,loot,end,pos,0,1);
    }
    else if (r%13==10) adventurer(hpmax,hpnow,aces,inv,slave,map,loot,end,pos);
    else if (r%13==0) {
        printf("The room is empty... but maybe there is something interesting!\n");
        treasure(hpmax,hpnow,aces,inv,slave,map,loot,end,pos,0,1);
    }
    else combat(hpmax,hpnow,aces,inv,slave,map,loot,end,pos,r);
}

void justadebugend(int* end){
    int i;
    printf("JUSTADEBUGEND!: Do you want to exit? [0]: No [1]: Yes\n");
    scanf("%d",&i);
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


void genmap(int* map, int* loot) {
    struct timespec a;
    a.tv_sec  = 0;
    a.tv_nsec = 1000;
    nanosleep( &a, NULL );
    struct timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);
    int i;
    for (i=0; i<12; i++) {
        *(map+i)=rand()%54;
        *(loot+i)=rand()%54;
    }
}

int checkend(int* hpnow, int* aces, int deb) {
    if (*hpnow<1) return -1;
    if ((*aces)&&(*(aces+1))&&(*(aces+2))&&(*(aces+3))) return 1;
    if ((DEBUG)&&(deb==4)) return 4;
    return 0;
}

void movement(int* map, int* loot, int* pos, int* floor, int* start) {
    int e=0;
    printf("Where do you want to go?\n[0]: Nowhere\n");
    if (*pos-4>=0) printf("[1]: North\n");
    if (*pos%4) printf("[4]: West\n");
    if (*pos%4!=3) printf("[6]: East\n");
    if (*pos+4<12) printf("[8]: South\n");
    if (*(map+*pos)==-1) printf("[-1]: Down\n");
    scanf("%d",&e);
    if (e==0) return;
    if ((e==1)&&(pos-4>=0)) {
        *pos=*pos-4;
        *start=1;
        return;
    }
    if ((e==4)&&(*pos%4)) {
        *pos=*pos-1;
        *start=1;
        return;
    }
    if ((e==6)&&(*(pos)%4!=3)) {
        *pos=*pos+1;
        *start=1;
        return;
    }
    if ((e==8)&&(*pos+4<12)) {
        *pos=*pos+4;
        *start=1;
        return;
    }
    if ((e==-1)&&(*(map+*pos)==-1)) {
        *floor=*floor+1;
        genmap(map,loot);
        *start=1;
        return;
    }
    printf("That's not an available direction!\n");
}

void useitem(int* hpmax, int* hpnow, int* inv) {
    int k;
    printf("What item do you want to use?\n");
    scanf("%d",&k);
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
    *(inv+k)=0;
    char s[20];
    nameitem(s,*(inv+k));
    printf("You use %s!\n",s);
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

int magiccount(int* inv) {
    int value=0;
    int i;
    for (i=0; i<INVNUM; i++) {
        if ((*(inv+i)>25)&&(*(inv+i)<35)) value+=(*(inv+i)%13)+1;
    }
    return value;
}

void magic(int* hpmax, int* hpnow, int* aces, int* inv, int* slave, int* map, int* loot, int* end, int* pos, int combat) {
    int v=magiccount(inv);
    int k;
    if (v==0) {
        printf("You don't have magic potions");
        return;
    }
    if (v>=1) printf("What spell do you want to cast?\n[0]: Nothing\n[1]: RemoteVision\n[2]: FuturePerception\n");
    if (v>=2) printf("[3]: Healing\n");
    if ((v>=3)&&(combat==1)) printf("[4]: Escape\n");
    if (v>=4) {
        if (combat==-1) printf("[5]: Illusion");
        if (combat==1) printf("[6]: Paralysis\n[7]: DoubleAttack\n");
    }
    if (v>=5) {
        if (combat==1) printf("[8]: SuperStrength\n");
        printf("[9]: AntiMagic\n");
    }
    if ((v>=6)&&(combat==1)) printf("[10]: StealingSpirit\n");
    if (v>=7) printf("[11]: BodySwitch\n");
    if (v>=8) printf("[12]: Teleport\n");
    if (v>=9) printf("[13]: Revelation\n[14]: HellBomb\n");
    if (v>=10) printf("[15]: Curse\n");
    if (v>=11) printf("[16]: GenieofLuck\n");
    if (v>=15) printf("[17]: StoneStatue\n[18]: GodVision\n");
    scanf("%d",&k);
    if (k==0) return;
    /*if ((k==1)&&(v>=1)) remotevision();
    else if ((k==2)&&(v>=1)) futureperception();
    else if ((k==3)&&(v>=2)) healing();
    else if ((k==4)&&(v>=3)&&(combat==1)) escape();
    else if ((k==5)&&(v>=4)&&(combat==-1)) illusion();
    else if ((k==6)&&(v>=4)&&(combat==1)) paralysis();
    else if ((k==7)&&(v>=4)&&(combat==1)) doubleattack();
    else if ((k==8)&&(v>=5)&&(combat==1)) superstrength();
    else if ((k==9)&&(v>=5)) antimagic();
    else if ((k==10)&&(v>=6)&&(combat==1)) stealingspirit();
    else if ((k==11)&&(v>=7)) bodyswitch();
    else if ((k==12)&&(v>=8)) teleport();
    else if ((k==13)&&(v>=9)) revelation();
    else if ((k==14)&&(v>=9)) hellbomb();
    else if ((k==15)&&(v>=10)) curse();
    else if ((k==16)&&(v>=11)) genieofluck();
    else if ((k==17)&&(v>=15)) stonestatue();
    else if ((k==18)&&(v>=15)) godvision();
    else printf("You can't do that!\n");*/
}

//fare un parser per una migliore gestione dei comandi

//una funzione per salvare?

//ovviamente bisogna controllare che tutte le regole siano implementate

int main(){
    struct timespec a;
    a.tv_sec  = 0;
    a.tv_nsec = 1000;
    nanosleep( &a, NULL );
    struct timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);
    printf("Welcome to Hebrac's Dungeon! ATM only the vanilla play is available :(\n");
    int hpmax=15, hpnow=15;
    int aces[4]={0,0,0,0};
    int inv[INVNUM]; //no limitazione inventario; farlo tramite array dinamici?
    int slave[INVNUM]; //no limitazione inventario; farlo tramite array dinamici?
    int start;
    for (start=0; start<INVNUM; start++) {
        inv[start]=0;
        slave[start]=0;
    }
    int map[12],loot[12];
    genmap(map,loot);
    int floor=0, end=0;
    int pos=2;
    int k;
    do {
        printf("Where do you want to enter?\n[1]: Northwest\n[3]: Northeast\n[7]: Southwest\n[9]: Southeast\n");
        scanf("%d",&start);
        if (start==1) pos=0;
        else if (start==3) pos=3;
        else if (start==7) pos=8;
        else if (start==9) pos=11;
        else {
            pos=1;
            printf("You lost one day to decide where to enter!\n");
        }
    } while (pos==1);
    start=1;
    do {
        if (start==1) {
            start=0;
            room(&hpmax,&hpnow,aces,inv,slave,map,loot,&end,&pos);
            if (*(map+pos)>=0) *(map+pos)=-2;
        }
        end=checkend(&hpnow,aces,k);
        if (end==0) {
            genstairs(map,&pos);
            printf("What do you want to do?\n[0]: Movement\n[1]: Magic\n[2]: Item\n");
            if (*(loot+pos)>0) printf("[3]: Treasure\n");
            if (DEBUG) printf("[4]: EXIT\n");
            scanf("%d",&k);
            if (k==0) movement(map,loot,&pos,&floor,&start);
            else if (k==1) /*magic!*/;
            else if (k==2) useitem(&hpmax,&hpnow,inv);
            else if ((k==3)&&(*(loot+pos)>0)) treasure(&hpmax,&hpnow,aces,inv,slave,map,loot,&end,&pos,0,1);
            else if ((k==4)&&(DEBUG)) justadebugend(&end);
            else printf("What?\n");
        }
        end=checkend(&hpnow,aces,k);
    } while (end==0);
    if (DEBUG) exitstatus(hpmax,hpnow,aces,inv,slave,map,loot,pos);
    if (end==1) printf("You win! Maybe I will find a better endscreen :P\n");
    else printf("You lose!\n");
}
