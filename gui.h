#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#define num_columns 4   //Number of columns for list
#define num_models 2    //Number of car models for drop down list

    GtkWidget    *ImgBtnBack;       //Image for the back button  
    GtkWidget    *BtnMainWindow;    //Back button

    GtkWidget    *FrmPrincipal;     //Main window
    GtkWidget    *LblTitle;         //Label for main window
    GtkWidget    *BtnClose;         //Exit button
    GtkWidget    *BtnAttackOne;     //Button to go to attackOne window
    GtkWidget    *BtnAttackAll;     //Button to go to attackAll window
    GtkWidget    *Layout;           //Layout for main window
    GtkWidget    *Image;            //Background image

    GtkWidget    *LblTitleOne;  //Label for attackOne window
    GtkWidget    *LblTitleAll;  //Label for attackAll window

//widgets for attack one window  
    GtkWidget    *List;          //List
    GtkWidget    *EntryID;       //Entry for id
    GtkWidget    *LblID;         //Label for entry id
    GtkWidget    *ComboboxModel; //Drop down list for car models
    GtkWidget    *LblModel;      //Label for drop down list
    GtkWidget    *EntryBox;      //Container for ListBox
    GtkWidget    *ButtonEntry;   //Button for attack
    GtkWidget    *ScrolledWndow; //Scrolled window for the list
    GtkTreeSelection *Selection; //List selection
    GtkWidget    *ListBox;       //Container for scrolledwindow, entrybox and buttonentry
    
//widgets for attack all window
    GtkWidget    *List2;           //List
    GtkWidget    *ScrolledWndow2;  //Scrolled window for the list
    GtkWidget    *ListBox2;        //Container for scrolledwindow and gif attacking
    GtkWidget    *ButtonAttack;    //Button for attack
    GtkWidget    *ButtonStop;      //Button for stop attack
    GdkPixbufAnimation *Animation; //Animation for load a gif
    GtkWidget    *ImageRadar;      //Image to display the animation
    GtkWidget    *LblImg;          //Label for imageradar


    
//Hidden widgets in main window
void hide_first(){
    gtk_widget_hide(BtnMainWindow);
    gtk_widget_hide(LblTitleOne);
    gtk_widget_hide(LblTitleAll);
    gtk_widget_hide(ListBox);
    gtk_widget_hide(ImageRadar);
    gtk_widget_hide(LblImg);
    gtk_widget_hide(ButtonStop);
    gtk_widget_hide(ListBox2);
}

//Hidden and shown widgets in attackOne window
void show_attOne_widgets(GtkWidget *button){
    gtk_widget_hide(LblTitle);
    gtk_widget_hide(BtnAttackOne);
    gtk_widget_hide(BtnAttackAll);
    gtk_widget_hide(BtnClose);

    gtk_widget_show(BtnMainWindow);
    gtk_widget_show(LblTitleOne);
    gtk_widget_show(ListBox);

    enableSniperMode();
}

void show_attAll_widgets(GtkWidget *button){
    gtk_widget_hide(LblTitle);
    gtk_widget_hide(BtnAttackOne);
    gtk_widget_hide(BtnAttackAll);
    gtk_widget_hide(BtnClose);

    gtk_widget_show(BtnMainWindow);
    gtk_widget_show(LblTitleAll);
    gtk_widget_show(ListBox2);

    enableSniperMode();
}

//Function for BtnMainWindow. Resets current window and returns to main window
void go_main_window(GtkWidget *button){
    gtk_tree_selection_set_mode(Selection, GTK_SELECTION_NONE);
    gtk_tree_selection_set_mode(Selection, GTK_SELECTION_SINGLE);

    gtk_entry_set_text(GTK_ENTRY(EntryID), "");

    gtk_combo_box_set_active_id (GTK_COMBO_BOX(ComboboxModel), NULL);
    
    gtk_widget_show_all(FrmPrincipal);
    hide_first();

    disableDisasterMode();
    disableSniperMode();
}

//Initialize the list
void SbListInit(GtkWidget *List, GtkWidget *scrolledwindow){
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkListStore *store;

    const gchar *column_names[num_columns] = {"ID", "TYPE", "TEMPERATURE", "PRESSURE"};
    
    int i;
    for(i = 0; i < num_columns; i++){
        //Create a cell
        renderer = gtk_cell_renderer_text_new();

        //Create a cell using the previous cell
        column = gtk_tree_view_column_new_with_attributes(column_names[i], //Column text(header)
                                                            renderer, //Cell
                                                            "text", //Cell type
                                                            i, //Column
                                                            NULL); //Attribute end

        //Add column to list
        gtk_tree_view_append_column(GTK_TREE_VIEW(List), column);
    }


    //Create the model
    store = gtk_list_store_new(num_columns, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    //Set model to the list
    gtk_tree_view_set_model(GTK_TREE_VIEW(List), GTK_TREE_MODEL(store));
    //Add list to scrolled window
    gtk_container_add(GTK_CONTAINER(scrolledwindow), List);
    //Remove model with the view
    g_object_unref(store);
                                                    
}

//Remove all rows from the list store
void SbListClear(GtkWidget *List){
    GtkListStore *store; //Model
    //Get model
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(List)));
    //Remove all rows from the list store
    gtk_list_store_clear(store);
}

//Insert elements in the list
void SbListInsert(GtkWidget *List, const gchar *str, const gchar *str2, const gchar *str3, const gchar *str4){
    GtkListStore *store; //Model
    GtkTreeIter iter; //Item

    //Get model
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(List)));

    //Appends a new row to the list
    gtk_list_store_append(store, //model
                            &iter); //item

    //Sets the value of one or more cells in the row referenced by iter
    gtk_list_store_set(store, //Model
                        &iter, //Item
                        0, str, //Pairs of column number and value(text), terminated with -1
                        1, str2,
                        2, str3,
                        3, str4,
                        -1);
}

//funtion button attack on attackone window
void function_btnAttack(GtkWidget *widget){

}

//Changes the active row of drop down list
void SbListChange(GtkWidget *widget){
    GtkTreeIter iter; //Item
    GtkTreeModel *model; //Model    
    gchar *value; //Element content
    

    //Sets iter to the currently selected node 
    if(gtk_tree_selection_get_selected(GTK_TREE_SELECTION(widget), &model, &iter)){
        //Gets the value of first cell in the row referenced by iter. 
        gtk_tree_model_get(model, &iter, 0, &value, -1);
        //Sets the text in the widget to the given value
        gtk_entry_set_text(GTK_ENTRY(EntryID), value);

        //Gets the value of second cell in the row referenced by iter. 
        gtk_tree_model_get(model, &iter, 1, &value, -1);
        //Changes the active row of comboboxModel to the one that has an ID equal to second parameter      
        if(g_strcmp0(value, "Toyota") == 0){
	        gtk_combo_box_set_active_id (GTK_COMBO_BOX(ComboboxModel), "Toyota");
        }else if(g_strcmp0(value, "Citroen") == 0){
            gtk_combo_box_set_active_id (GTK_COMBO_BOX(ComboboxModel), "Citroen");
        }

        g_signal_connect(ButtonEntry, "clicked", G_CALLBACK(function_btnAttack), NULL);

        g_free(value);
    }
}

//Create list with scroll window
void create_list(GtkWidget **list, GtkWidget **listbox, GtkWidget **scrolledwindow){
    
    *list = gtk_tree_view_new();
    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(*list), TRUE);
    
    //Create vertical container for the list
    *listbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(*listbox, 350, 300);

    *scrolledwindow = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(*scrolledwindow, 200, 200);

    //Add scrolled window to vertical container
    gtk_box_pack_start(GTK_BOX(*listbox), *scrolledwindow, FALSE, FALSE, 0);


}

void gturnOff() {
    turnOff();
    disableSniperMode();
    disableDisasterMode();
    gtk_main_quit();
    //pthread_exit();
}

//AttackOne window
void attOneWindow(){
    const gchar *model_names[num_models] = {"Toyota", "Citroen"};

    LblTitleOne = gtk_label_new("Attack One");
    gtk_layout_put(GTK_LAYOUT(Layout), LblTitleOne, 189, 40);
    gtk_widget_set_size_request(LblTitleOne, 80, 30);
    //name for css
    gtk_widget_set_name(LblTitleOne,"LblTitleOne");

    create_list(&List, &ListBox, &ScrolledWndow);

    //Create widgets for attackOne window
    LblID = gtk_label_new("ID:");
    gtk_widget_set_size_request(LblID, 50, 30);
    //name for css
    gtk_widget_set_name(LblID,"LblID");

    LblModel = gtk_label_new("MODEL:");
    gtk_widget_set_size_request(LblModel, 50, 30);
    //name for css
    gtk_widget_set_name(LblModel,"LblModel");

    EntryID = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(EntryID), 8);

    //Create drop down list and add options
    ComboboxModel = gtk_combo_box_text_new();
    int i;
    for(i = 0; i < num_models; i++){
        gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT (ComboboxModel), model_names[i], model_names[i]);
    }
    

    //Create attack button
    ButtonEntry = gtk_button_new_with_label("Attack");
    gtk_widget_set_size_request(ButtonEntry, 80, 25);


    //Create horizontal container for entry and combobox
    EntryBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(ListBox, 350, 50);

    //Add widgets to horizontal container
    gtk_box_pack_start(GTK_BOX(EntryBox), LblID, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(EntryBox), EntryID, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(EntryBox), LblModel, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(EntryBox), ComboboxModel, TRUE, TRUE, 5);

    //Add horizontal conatiner to vertical container
    gtk_box_pack_start(GTK_BOX(ListBox), EntryBox, FALSE, FALSE, 5);

    //Add button entry to ListBox
    gtk_box_pack_start(GTK_BOX(ListBox), ButtonEntry, FALSE, FALSE, 5);
    

    //Add listBox to layout
    gtk_layout_put(GTK_LAYOUT(Layout), ListBox, 54, 100);

    //Initialize the list
    SbListInit(List, ScrolledWndow);

    //Remove all rows from the list
    SbListClear(List);

    //Insert elements in the list
    SbListInsert(List, "fb26ac5a", "Toyota", "15.000", "253.382");
    SbListInsert(List, "fb26ac5b", "Toyota", "14.000", "242.792");
    SbListInsert(List, "fb26ac5c", "Toyota", "14.000", "333.382");
    SbListInsert(List, "8a58b6a2", "Citroen", "18.000", "242.792");
    SbListInsert(List, "8a58f9a2", "Citroen", "13.000", "253.382");
    SbListInsert(List, "7a58f9a1", "Citroen", "14.000", "242.792");

    //Get the selection associated with the list
    Selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(List));
    
    g_signal_connect(Selection, "changed", G_CALLBACK(SbListChange), NULL);
    
}

void attacking_all(GtkWidget *button){
    gtk_widget_hide(ButtonAttack);
    gtk_widget_show(ButtonStop);
    gtk_widget_show(ImageRadar);
    gtk_widget_show(LblImg);
}

void stop_attacking_all(GtkWidget *button){
    gtk_widget_hide(ButtonStop);
    gtk_widget_hide(ImageRadar);
    gtk_widget_hide(LblImg);
    gtk_widget_show(ButtonAttack);
}

//AttackAll window
void attAllWindow(){
    LblTitleAll = gtk_label_new("Attack All");
    gtk_layout_put(GTK_LAYOUT(Layout), LblTitleAll, 189, 40);
    gtk_widget_set_size_request(LblTitleAll, 80, 30);
    //name for css
    gtk_widget_set_name(LblTitleAll,"LblTitleAll");


    create_list(&List2, &ListBox2, &ScrolledWndow2);

    //name for css
    gtk_widget_set_name(List2,"List2");

    //Creates attack button
    ButtonAttack = gtk_button_new_with_label("Attack");
    gtk_widget_set_size_request(ButtonAttack, 80, 25);

    //Creates attack button
    ButtonStop = gtk_button_new_with_label("Stop");
    gtk_widget_set_size_request(ButtonStop, 80, 25);
    

    LblImg = gtk_label_new("Attacking...");
    gtk_widget_set_size_request(LblImg, 50, 30);
    //name for css
    gtk_widget_set_name(LblImg,"LblImg");

    //Creates a new animation by loading it from a file
    Animation = gdk_pixbuf_animation_new_from_file("./img/radar2.gif", NULL);
    //Creates an image displaying the given animation
    ImageRadar = gtk_image_new_from_animation(Animation);

    
    //Add button attack to ListBox2
    gtk_box_pack_start(GTK_BOX(ListBox2), ButtonAttack, FALSE, FALSE, 5);
    //Add button stop to ListBox2
    gtk_box_pack_start(GTK_BOX(ListBox2), ButtonStop, FALSE, FALSE, 5);

    gtk_box_pack_start(GTK_BOX(ListBox2), ImageRadar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(ListBox2), LblImg, FALSE, FALSE, 0);

    //Add listBox2 to layout
    gtk_layout_put(GTK_LAYOUT(Layout), ListBox2, 54, 80);

    //Initialize the list
    SbListInit(List2, ScrolledWndow2);

    //Remove all rows from the list
    SbListClear(List2);

    //Insert elements in the list
    SbListInsert(List2, "fb26ac5a", "Toyota", "15.000", "253.382");
    SbListInsert(List2, "fb26ac5b", "Toyota", "14.000", "242.792");
    SbListInsert(List2, "fb26ac5c", "Toyota", "14.000", "333.382");
    SbListInsert(List2, "8a58b6a2", "Citroen", "18.000", "242.792");
    SbListInsert(List2, "8a58f9a2", "Citroen", "13.000", "253.382");
    SbListInsert(List2, "7a58f9a1", "Citroen", "14.000", "242.792");
    SbListInsert(List2, "fb26ac5a", "Toyota", "15.000", "253.382");
    SbListInsert(List2, "fb26ac5b", "Toyota", "14.000", "242.792");
    SbListInsert(List2, "fb26ac5c", "Toyota", "14.000", "333.382");
    SbListInsert(List2, "8a58b6a2", "Citroen", "18.000", "242.792");
    SbListInsert(List2, "8a58f9a2", "Citroen", "13.000", "253.382");
    SbListInsert(List2, "7a58f9a1", "Citroen", "14.000", "242.792");
    SbListInsert(List2, "fb26ac5a", "Toyota", "15.000", "253.382");
    SbListInsert(List2, "fb26ac5b", "Toyota", "14.000", "242.792");
    SbListInsert(List2, "fb26ac5c", "Toyota", "14.000", "333.382");
    SbListInsert(List2, "8a58b6a2", "Citroen", "18.000", "242.792");
    SbListInsert(List2, "8a58f9a2", "Citroen", "13.000", "253.382");
    SbListInsert(List2, "7a58f9a1", "Citroen", "14.000", "242.792");


    g_signal_connect(ButtonAttack, "clicked", G_CALLBACK(attacking_all), NULL);
    g_signal_connect(ButtonStop, "clicked", G_CALLBACK(stop_attacking_all), NULL);

}

//Main window
void MainWindow(){

    //Create widgets for main window and add to layout
    FrmPrincipal = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(FrmPrincipal), 458, 458);
    gtk_window_set_position(GTK_WINDOW(FrmPrincipal), GTK_WIN_POS_CENTER);
    Layout = gtk_layout_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER (FrmPrincipal), Layout);
    gtk_widget_show(Layout);

    Image = gtk_image_new_from_file("./img/coche2.jpg");
    gtk_layout_put(GTK_LAYOUT(Layout), Image, 0, 0);

    LblTitle = gtk_label_new("ctOS-TPMS");
    gtk_layout_put(GTK_LAYOUT(Layout), LblTitle, 189, 40);
    gtk_widget_set_size_request(LblTitle, 80, 30);
    //name for css
    gtk_widget_set_name(LblTitle,"LblTitle");

    BtnClose = gtk_button_new_with_label("Exit");
    gtk_layout_put(GTK_LAYOUT(Layout), BtnClose, 189, 380);
    gtk_widget_set_size_request(BtnClose, 80, 35);

    BtnAttackOne = gtk_button_new_with_label("Attack One"); 
    gtk_layout_put(GTK_LAYOUT(Layout), BtnAttackOne, 79, 330);
    gtk_widget_set_size_request(BtnAttackOne, 140, 35);
    
    BtnAttackAll = gtk_button_new_with_label("Attack All");
    gtk_layout_put(GTK_LAYOUT(Layout), BtnAttackAll, 239, 330);
    gtk_widget_set_size_request(BtnAttackAll, 140, 35);   

    BtnMainWindow = gtk_button_new();
    gtk_layout_put(GTK_LAYOUT(Layout), BtnMainWindow, 10, 10);
    gtk_widget_set_size_request(BtnMainWindow, 30, 30); 

    ImgBtnBack = gtk_image_new_from_file ("./img/back_6.png");

    gtk_button_set_image (GTK_BUTTON (BtnMainWindow), ImgBtnBack);

    attOneWindow(); 

    attAllWindow();
    
    g_signal_connect(BtnClose, "clicked", G_CALLBACK(gturnOff), NULL);
    g_signal_connect(BtnAttackOne, "clicked", G_CALLBACK(show_attOne_widgets), NULL);
    g_signal_connect(BtnAttackAll, "clicked", G_CALLBACK(show_attAll_widgets), NULL);
    g_signal_connect(BtnMainWindow, "clicked", G_CALLBACK(go_main_window), NULL);
    g_signal_connect(FrmPrincipal, "destroy", G_CALLBACK(gturnOff), NULL);

    gtk_widget_show_all(FrmPrincipal);
    hide_first();

}

int initGUI() {
    gtk_init(NULL, NULL);
    
    //style css
    GtkCssProvider *provider;
	GdkDisplay *display;
	GdkScreen *screen;

    provider = gtk_css_provider_new ();
    gtk_css_provider_load_from_path (provider,"./CSS/style.css", NULL);
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER(provider), 
                                                GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    
    MainWindow();

    //Runs the main loop until gtk_main_quit() is called             
    gtk_main();

    return 0;
}