//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TTimer *Timer1;
        TLabel *Label1;
        TTimer *Timer2;
        TTimer *Timer3;
        TImage *Image1;
        TImage *Image2;
        TTimer *Timer4;
        TButton *Button1;
        TLabel *Label2;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Timer2Timer(TObject *Sender);
        void __fastcall Timer3Timer(TObject *Sender);
        void __fastcall Timer4Timer(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
class move{
  private:
    TForm *f;
  protected:
    void __fastcall timer1(TObject *Sender);
    TImage *im;
    TTimer *t1;
    int dy;
  public:
    move(TForm *f,int dy);
    ~move();
};
class role:public move{
  private:
    TImage *im2;
    TShape *sh[10];
    void __fastcall timer1(TObject *Sender);
  protected:
    TTimer *t2;
    int hp;
  public:
    role(TForm *f,TImage *im2,TPanel *p);
    void control_movement(int dx);
    int get_top();
    int get_left();
    int get_height();
    int get_width();
    void follow(int n);
    int get_tag();
    ~role();
};
class stairs:public move{
  private:
    void __fastcall timer2(TObject *Sender);
  protected:
    TTimer *t2;
    role *ro;
  public:
    stairs(TForm *f,role *ro,int top ,int left);
    bool collision(role *x);
    int get_tag();
    ~stairs();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
 