#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>


#define num_columns 4   //Number of columns for list
#define num_models 3    //Number of car models for drop down list

#define REFRESH_VIEW 5
#define GIF_TIME_ATTONE 3

    extern GtkWidget    *ImageButtonBack;     //Image for the back button  
    extern GtkWidget    *ButtonMainWindow;    //Back button

    extern GtkWidget    *FrmPrincipal;     //Main window
    extern GtkWidget    *LabelMainTitle;   //Label for main window
    extern GtkWidget    *ButtonExit;       //Exit button
    extern GtkWidget    *ButtonGo_AO;      //Button to go to _AO window
    extern GtkWidget    *ButtonGo_AA;      //Button to go to _AA window
    extern GtkWidget    *Layout;           //Layout for main window
    extern GtkWidget    *BackgroundImage;  //Background image

    extern GtkWidget    *LabelTitle_AO;  //Label for _AO window
    extern GtkWidget    *LabelTitle_AA;  //Label for _AA window

//widgets for attack one window 
    extern GTimer       *Timer;
    extern GtkWidget    *List_AO;              //List
    extern GtkWidget    *EntryID_AO;           //Entry for id
    extern GtkWidget    *LabelID_AO;           //Label for entry id
    extern GtkWidget    *ComboboxModel_AO;     //Drop down list for car models
    extern GtkWidget    *LabelModel_AO;        //Label for drop down list
    extern GtkWidget    *EntryBox_AO;          //Container for LabelID_AO, EntryID_AO, ComboboxModel_AO and LabelModel_AO
    extern GtkWidget    *ButtonPlay_AO;        //Button for attack
    extern GtkWidget    *ScrolledWndow_AO;     //Scrolled window for the list
    extern GtkTreeSelection *SelectionList_AO; //List selection
    extern GtkWidget    *ListBox_AO;           //Container for scrolledwindow, EntryBox_AO and ButtonPlay_AO
    extern GdkPixbufAnimation *Animation_AO;   //Animation for load a gif
    extern GtkWidget    *ImageGif_AO;          //Image to display the animation
    
//widgets for attack all window
    extern GtkWidget    *List_AA;              //List
    extern GtkWidget    *ScrolledWndow_AA;     //Scrolled window for the list
    extern GtkWidget    *ListBox_AA;           //Container for scrolledwindow and gif attacking
    extern GtkWidget    *ButtonPlay_AA;        //Button for attack
    extern GtkWidget    *ButtonStop_AA;        //Button for stop attack
    extern GdkPixbufAnimation *Animation_AA;   //Animation for load a gif
    extern GtkWidget    *ImageGif_AA;          //Image to display the animation
    extern GtkWidget    *LabelImageGif_AA;     //Label for ImageGif_AA


gboolean refreshTimer();
    
void hide_first(); //Hidden widgets in main window

void show_attOne_widgets(GtkWidget *button);//Hidden and shown widgets in attackOne window
void show_attAll_widgets(GtkWidget *button);//Hidden and shown widgets in attackAll window

void go_main_window(GtkWidget *button); //Function for ButtonMainWindow. Resets current window and returns to main window

void SbListInit(GtkWidget *List, GtkWidget *scrolledwindow);//Initialize the list
void SbListClear(GtkWidget *List); //Remove all rows from the list store
void SbListInsert(GtkWidget *List, const gchar *str, const gchar *str2, const gchar *str3, const gchar *str4);//Insert elements in the list
void SbListChange(GtkWidget *widget); //Changes the active row of drop down list

gboolean refreshImageGif_AO();

void function_ButtonAttack(GtkWidget *widget);//funtion button attack on attackone window

void create_list(GtkWidget **list, GtkWidget **listbox, GtkWidget **scrolledwindow); //Create list with scroll window

void gturnOff(); //function for exit button

void attOneWindow();//AttackOne window

void attacking_all(GtkWidget *button); //funtion button attack on attackall window
void stop_attacking_all(GtkWidget *button); //funtion button stop on attackall window

void attAllWindow(); //AttackAll window

void MainWindow();//Main window

int initGUI(); //Initialize the gui