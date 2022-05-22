#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"madoka.h"
Entity *Entity_ctor(Entity *this){(*this).hp=100,(*this).is_dead=Entity_is_dead;return this;}
void Entity_dtor(Entity *this){}
int Entity_is_dead(void *this){return (*(Entity*)this).hp<=0;}
Shoujo *Shoujo_ctor(Shoujo *this, const char *name, const char *wish){
	Entity_ctor((Entity*)this);
	(*this).name=(char*)name;
	(*this).name=calloc(strlen(name)+1,1);
	strncpy((*this).name,name,strlen(name)+1);
	(*this).wish=calloc(strlen(wish)+1,1);
	strncpy((*this).wish,wish,strlen(wish)+1);
	(*this).kimoji=100;
	(*this).is_dead=Entity_is_dead;
	(*this).is_despair=Shoujo_is_despair;
	(*this).do_wish=Shoujo_do_wish;
	(*this).despair=Shoujo_despair;
	return this;
};
void Shoujo_dtor(Shoujo *this){free((*this).name);free((*this).wish);}
int Shoujo_is_despair(void *this){return (*(Shoujo*)this).kimoji<=-100;}
void Shoujo_do_wish(void *this){puts((*(Shoujo*)this).wish);}
void Shoujo_despair(void *this){(*(Shoujo*)this).base.hp=0;}
Mahoushoujo *Mahoushoujo_ctor(Mahoushoujo *this, const char *name, const char *wish, Skill skill){
	Shoujo_ctor((Shoujo*)this,name,wish);
	(*(Entity*)this).hp*=3;
	(*this).atk=100;
	(*this).is_dead=Entity_is_dead;
	(*this).do_wish=(*this).base.do_wish=Mahoushoujo_do_wish;
	(*this).base.despair=Mahoushoujo_despair;
	(*this).attack=Mahoushoujo_attack;
	(*this).skill=skill;
	return this;
}
void Mahoushoujo_dtor(Mahoushoujo *this){Shoujo_dtor((Shoujo*)this);}
void Mahoushoujo_do_wish(void *this){puts((*(Shoujo*)this).wish);puts("But nothing is good");(*(Shoujo*)this).kimoji-=10;}
void Mahoushoujo_attack(Mahoushoujo *this, Entity *enemy){(*enemy).hp-=(*this).atk;}
void Mahoushoujo_despair(void *this){puts("Watashii de, hondo baga");}
Majo *Majo_ctor(Majo *this, const char *name, const char *wish){
	Shoujo_ctor((Shoujo*)this,name,wish);
	(*(Entity*)this).hp*=50;
	(*this).atk=10;
	(*this).is_dead=Entity_is_dead;
	(*this).base.despair=Majo_despair;
	(*this).attack=Majo_attack;
	(*this).kekkai=Majo_kekkai;
	return this;
}
void Majo_dtor(Majo *this){Shoujo_dtor((Shoujo*)this);}
void Majo_attack(Majo *this, Entity *enemy){(*enemy).hp-=(*this).atk;}
void Majo_kekkai(Majo *this, Shoujo *sj){(*sj).kimoji-=100;}
void Majo_despair(void *this){}
Majo *mhsj_to_mj(Mahoushoujo *mhsj){
	Majo *p=Majo_ctor(malloc(sizeof(Majo)),(*(Shoujo*)mhsj).name,(*(Shoujo*)mhsj).wish);
	Mahoushoujo_dtor(mhsj);
	free(mhsj);
	return p;
}
void Madoka_skill(void *this, void *target){puts("Madoka become god, end.");exit(0);}
void Homura_skill(void *this, void *target){if((*(Entity*)this).hp<50)puts("This round is hopeless, Homura go to next round."),exit(0);}
void Sayaka_skill(void *this, void *target){(*(Entity*)this).hp+=30;(*(Shoujo*)this).kimoji-=30;}
void Kyoko_skill(void *this, void *target){if(!strcmp((*(Shoujo*)target).name,"Sayaka"))(*(Entity*)this).hp=0,(*(Entity*)target).hp=0;}

