//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
stairs *st[7];
role *ro;
int layers=0;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
   srand(time(NULL));
   ro=new role(Form1,Image1,Panel1);
   st[0]=new stairs(Form1,ro,200,100);
}
//---------------------------------------------------------------------------
move::move(TForm *f,int dy){
  this->f=f;
  this->dy=dy;
  t1=new TTimer(f);
  t1->Interval=120;
  t1->OnTimer=timer1;
  t1->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall move::timer1(TObject *Sender){
  im->Top=im->Top+dy;
  if(im->Top<50 && im->Tag==1) im->Top=im->Top+45;
  if(im->Top<50 && im->Tag==2) im->Tag=0;
  if(im->Top>f->ClientHeight){
     t1->Enabled=false;
     im->Tag=0;
     im->Visible=false;
  }
  if(dy<0 && im->Tag==1) dy=-dy;
}
//---------------------------------------------------------------------------
move::~move(){
  delete t1;
}
//---------------------------------------------------------------------------
role::role(TForm *f,TImage *im2,TPanel *p):move(f,10){
  this->im2=im2;
  hp=9;
  for(int i=0;i<10;i++){
    sh[i]=new TShape(p);
    sh[i]->Parent=p;
    sh[i]->Height=18;
    sh[i]->Width=8;
    sh[i]->Brush->Color=clRed;
    sh[i]->Pen->Color=clMenu;
    sh[i]->Top=17;
  }
  sh[0]->Left=2;  sh[5]->Left=54;
  sh[1]->Left=13; sh[6]->Left=64;
  sh[2]->Left=23; sh[7]->Left=74;
  sh[3]->Left=33; sh[8]->Left=84;
  sh[4]->Left=43; sh[9]->Left=95;
  im=new TImage(f);
  im->Parent=f;
  im->Tag=1;
  im->Picture->LoadFromFile("小朋友.jpg");
  im->Top=100;
  im->Left=100;
  im->Height=30;
  im->Width=30;
  im->Stretch=true;
  t1->Enabled=true;
  t2=new TTimer(f);
  t2->Interval=150;
  t2->OnTimer=timer1;
}
//---------------------------------------------------------------------------
void role::control_movement(int dx){
  if(im->Left>0 && dx<0){
    im->Left=im->Left+dx;
  }
  if(im->Left+im->Width < 380 && dx>0){
    im->Left=im->Left+dx;
  }
}
//---------------------------------------------------------------------------
void __fastcall role::timer1(TObject *Sender){
  int y1,y2,y3,y4,z1,z2,z3,z4;
  y1=im->Left; y2=im->Width+y1;
  z1=im->Top; z2=z1+im->Height;
  y3=im2->Left; y4=im2->Width+y3;
  z3=im2->Top; z4=z3+im2->Height;
  if((y1>=y3 && y1<=y4 && z1>=z3 && z1<=z4)||
    (y1>=y3 && y1<=y4 && z2>=z3 && z2<=z4)||
    (y2>=y3 && y2<=y4 && z1>=z3 && z1<=z4)||
    (y2>=y3 && y2<=y4 && z2>=z3 && z2<=z4)){
     if(hp>=0)hp=hp-2;
  }
  for(int i=9;i>hp;i--){
     sh[i]->Visible=false;
  }
  if(hp<=0) im->Tag=0;
}
//---------------------------------------------------------------------------
int role::get_top(){
  return im->Top;
}
//---------------------------------------------------------------------------
int role::get_left(){
  return im->Left;
}
//---------------------------------------------------------------------------
int role::get_height(){
  return im->Height;
}
//---------------------------------------------------------------------------
int role::get_width(){
  return im->Width;
}
//---------------------------------------------------------------------------
int role::get_tag(){
  return im->Tag;
}
//---------------------------------------------------------------------------
void role::follow(int n){
  if(dy>0) dy=n;
}
//---------------------------------------------------------------------------
role::~role(){
  delete t2;
  delete im;
  for(int i=0;i<10;i++){
    delete sh[i];
  }
}
//---------------------------------------------------------------------------
stairs::stairs(TForm *f,role *ro,int top,int left):move(f,-10){
  this->ro=ro;
  im=new TImage(f);
  im->Parent=f;
  im->Tag=2;
  im->Picture->LoadFromFile("階梯.jpg");
  im->Top=top;
  im->Left=left;
  im->Height=20;
  im->Width=80;
  im->Stretch=true;
  t1->Enabled=true;
  t2=new TTimer(f);
  t2->Interval=60;
  t2->OnTimer=timer2;
}
//---------------------------------------------------------------------------
void __fastcall stairs::timer2(TObject *Sender){
  if(collision(ro)){
     ro->follow(dy);
  }
}
//---------------------------------------------------------------------------
bool stairs::collision(role *x){
  int y1,y2,y3,y4,z1,z2,z3,z4;
  y1=im->Left; y2=im->Width+y1;
  z1=im->Top; z2=z1+im->Height;
  y3=x->get_left(); y4=x->get_width()+y3;
  z3=x->get_top(); z4=z3+x->get_height();
  if((y1>=y3 && y1<=y4 && z1>=z3 && z1<=z4)||
    (y1>=y3 && y1<=y4 && z2>=z3 && z2<=z4)||
    (y2>=y3 && y2<=y4 && z1>=z3 && z1<=z4)||
    (y2>=y3 && y2<=y4 && z2>=z3 && z2<=z4)||
    (y1<=y3 && y2>=y4 && z1>=z3 && z4>=z1)){
    return 1;
  }
  return 0;
}
//---------------------------------------------------------------------------
int stairs::get_tag(){
  return im->Tag;
}
//---------------------------------------------------------------------------
stairs::~stairs(){
  delete t2;
  delete im;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
  if(ro!=NULL)delete ro;
  for(int i=0;i<6;i++){
     if(st[i]!=NULL)delete st[i];
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  if(GetAsyncKeyState(37)&0x8000)ro->control_movement(-20);
  if(GetAsyncKeyState(39)&0x8000)ro->control_movement(20);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
  layers++;
  if(layers<10){
    Label1->Caption="地下000"+AnsiString(layers)+"階";
  }else if(layers<100){
    Label1->Caption="地下00"+AnsiString(layers)+"階";
  }else if(layers<1000){
    Label1->Caption="地下0"+AnsiString(layers)+"階";
  }else{
    Label1->Caption="地下"+AnsiString(layers)+"階";
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer3Timer(TObject *Sender)
{
  for(int i=0;i<6;i++){
     if(st[i]!=NULL){
       if(st[i]->get_tag()==0){
         delete st[i];
         st[i]=NULL;
       }
     }
  }
  int r2=rand()%200+80;
  for(int i=0;i<6;i++){
     if(st[i]==NULL){
       st[i]=new stairs(Form1,ro,550,r2);
       break;
     }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer4Timer(TObject *Sender)
{
  if(ro->get_tag()==0){
   Timer1->Enabled=false;
   Timer2->Enabled=false;
   Timer3->Enabled=false;
   Timer4->Enabled=false;
   delete ro;
   ro=NULL;
   for(int i=0;i<6;i++){
     delete st[i];
     st[i]=NULL;
   }
   layers=0;
   Button1->Visible=true;
   ShowMessage("失敗!");
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
  Label1->Caption="地下0000階";
  Timer1->Enabled=true;
  Timer2->Enabled=true;
  Timer3->Enabled=true;
  Timer4->Enabled=true;
  ro=new role(Form1,Image1,Panel1);
  st[0]=new stairs(Form1,ro,200,100);
  Button1->Visible=false;
}
//---------------------------------------------------------------------------

