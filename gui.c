#include "includes/gui.h"
#include "includes/controller.h"

    GtkWidget    *ImageButtonBack;     //Image for the back button  
    GtkWidget    *ButtonMainWindow;    //Back button

    GtkWidget    *FrmPrincipal;     //Main window
    GtkWidget    *LabelMainTitle;   //Label for main window
    GtkWidget    *ButtonExit;       //Exit button
    GtkWidget    *ButtonGo_AO;      //Button to go to _AO window
    GtkWidget    *ButtonGo_AA;      //Button to go to _AA window
    GtkWidget    *Layout;           //Layout for main window
    GtkWidget    *BackgroundImage;  //Background image

    GtkWidget    *LabelTitle_AO;  //Label for _AO window
    GtkWidget    *LabelTitle_AA;  //Label for _AA window

//widgets for attack one window 
    GTimer       *Timer;
    GtkWidget    *List_AO;              //List
    GtkWidget    *EntryID_AO;           //Entry for id
    GtkWidget    *LabelID_AO;           //Label for entry id
    GtkWidget    *ComboboxModel_AO;     //Drop down list for car models
    GtkWidget    *LabelModel_AO;        //Label for drop down list
    GtkWidget    *EntryBox_AO;          //Container for LabelID_AO, EntryID_AO, ComboboxModel_AO and LabelModel_AO
    GtkWidget    *ButtonPlay_AO;        //Button for attack
    GtkWidget    *ScrolledWndow_AO;     //Scrolled window for the list
    GtkTreeSelection *SelectionList_AO; //List selection
    GtkWidget    *ListBox_AO;           //Container for scrolledwindow, EntryBox_AO and ButtonPlay_AO
    GdkPixbufAnimation *Animation_AO;   //Animation for load a gif
    GtkWidget    *ImageGif_AO;          //Image to display the animation
    gint handler_id;
    
//widgets for attack all window
    GtkWidget    *List_AA;              //List
    GtkWidget    *ScrolledWndow_AA;     //Scrolled window for the list
    GtkWidget    *ListBox_AA;           //Container for scrolledwindow and gif attacking
    GtkWidget    *ButtonPlay_AA;        //Button for attack
    GtkWidget    *ButtonStop_AA;        //Button for stop attack
    GdkPixbufAnimation *Animation_AA;   //Animation for load a gif
    GtkWidget    *ImageGif_AA;          //Image to display the animation
    GtkWidget    *LabelImageGif_AA;     //Label for ImageGif_AA

gboolean refreshTimer() {
    if(!getDisasterMode() && !getSniperMode())
        return false;
    if(getSniperMode()){
        refreshView("AO");
    }else if(getDisasterMode()){
        refreshView("AA");
    }
    return true;
}

void hide_first(){
    gtk_widget_hide(ButtonMainWindow);
    gtk_widget_hide(LabelTitle_AO);
    gtk_widget_hide(LabelTitle_AA);
    gtk_widget_hide(ImageGif_AO);
    gtk_widget_hide(ListBox_AO);
    gtk_widget_hide(ImageGif_AA);
    gtk_widget_hide(LabelImageGif_AA);
    gtk_widget_hide(ButtonStop_AA);
    gtk_widget_hide(ListBox_AA);
}

void show_attOne_widgets(GtkWidget *button){
    gtk_widget_hide(LabelMainTitle);
    gtk_widget_hide(ButtonGo_AO);
    gtk_widget_hide(ButtonGo_AA);
    gtk_widget_hide(ButtonExit);

    gtk_widget_show(ButtonMainWindow);
    gtk_widget_show(LabelTitle_AO);
    gtk_widget_show(ListBox_AO);

    enableSniperMode();
    g_timeout_add_seconds(REFRESH_VIEW, refreshTimer, List_AO);
}

void show_attAll_widgets(GtkWidget *button){
    gtk_widget_hide(LabelMainTitle);
    gtk_widget_hide(ButtonGo_AO);
    gtk_widget_hide(ButtonGo_AA);
    gtk_widget_hide(ButtonExit);

    gtk_widget_show(ButtonMainWindow);
    gtk_widget_show(LabelTitle_AA);
    gtk_widget_show(ListBox_AA);

    g_timeout_add_seconds(REFRESH_VIEW, refreshTimer, List_AA);
}

void go_main_window(GtkWidget *button){
    gtk_tree_selection_set_mode(SelectionList_AO, GTK_SELECTION_NONE);
    gtk_tree_selection_set_mode(SelectionList_AO, GTK_SELECTION_SINGLE);

    gtk_entry_set_text(GTK_ENTRY(EntryID_AO), "");

    gtk_combo_box_set_active_id (GTK_COMBO_BOX(ComboboxModel_AO), NULL);
    
    gtk_widget_show_all(FrmPrincipal);
    hide_first();

    disableDisasterMode();
    disableSniperMode();
    killRTL433();
}

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

void SbListClear(GtkWidget *List){
    GtkListStore *store; //Model
    //Get model
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(List)));
    //Remove all rows from the list store
    gtk_list_store_clear(store);
}

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

gboolean refreshImageGif_AO(){
    gtk_widget_hide(ImageGif_AO);
    gtk_widget_set_sensitive(GTK_WIDGET(ButtonPlay_AO), true);
    return false;
}

void function_ButtonAttack(GtkWidget *widget){
    const gchar *id, *model; //Element content
    gtk_widget_set_sensitive(GTK_WIDGET(ButtonPlay_AO), false);
    gtk_widget_show(ImageGif_AO);
    g_timeout_add_seconds(GIF_TIME_ATTONE, refreshImageGif_AO, ImageGif_AO);
    
    id = gtk_entry_get_text(GTK_ENTRY(EntryID_AO));
    model = gtk_combo_box_get_active_id(GTK_COMBO_BOX(ComboboxModel_AO));
    //printf("%s\n", "ADIOOOOOOS");
    
    sniperModeAttack((char*)id, (char*)model); //Need fix thing on gui for do this better
}

void SbListChange(GtkWidget *widget){
    GtkTreeIter iter; //Item
    GtkTreeModel *model; //Model    
    gchar *value; //Element content

    //Sets iter to the currently selected node 
    if(gtk_tree_selection_get_selected(GTK_TREE_SELECTION(widget), &model, &iter)){
        //Gets the value of first cell in the row referenced by iter. 
        gtk_tree_model_get(model, &iter, 0, &value, -1);
        //Sets the text in the widget to the given value
        gtk_entry_set_text(GTK_ENTRY(EntryID_AO), value);

        //Gets the value of second cell in the row referenced by iter. 
        gtk_tree_model_get(model, &iter, 1, &value, -1);
        //Changes the active row of ComboboxModel_AO to the one that has an ID equal to second parameter      
        if(g_strcmp0(value, "Toyota") == 0){
	        gtk_combo_box_set_active_id (GTK_COMBO_BOX(ComboboxModel_AO), "Toyota");
        }else if(g_strcmp0(value, "Citroen") == 0){
            gtk_combo_box_set_active_id (GTK_COMBO_BOX(ComboboxModel_AO), "Citroen");
        }else if(g_strcmp0(value, "Renault") == 0){
            gtk_combo_box_set_active_id (GTK_COMBO_BOX(ComboboxModel_AO), "Renault");
        }
        
        

        g_free(value);
    }
}

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


void attOneWindow(){
    const gchar *model_names[num_models] = {"Toyota", "Citroen", "Renault"};

    LabelTitle_AO = gtk_label_new("Attack One");
    gtk_layout_put(GTK_LAYOUT(Layout), LabelTitle_AO, 160, 60);
    gtk_widget_set_size_request(LabelTitle_AO, 80, 30);
    //name for css
    gtk_widget_set_name(LabelTitle_AO,"LabelTitle_AO");

    create_list(&List_AO, &ListBox_AO, &ScrolledWndow_AO);
    gtk_widget_set_name(List_AO,"List_AO");

    //Create widgets for attackOne window
    LabelID_AO = gtk_label_new("ID:");
    gtk_widget_set_size_request(LabelID_AO, 50, 30);
    //name for css
    gtk_widget_set_name(LabelID_AO,"LabelID_AO");

    LabelModel_AO = gtk_label_new("MODEL:");
    gtk_widget_set_size_request(LabelModel_AO, 50, 30);
    //name for css
    gtk_widget_set_name(LabelModel_AO,"LabelModel_AO");

    EntryID_AO = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(EntryID_AO), 8);
    gtk_widget_set_name(EntryID_AO, "EntryID_AO");

    //Create drop down list and add options
    ComboboxModel_AO = gtk_combo_box_text_new();
    int i;
    for(i = 0; i < num_models; i++){
        gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT (ComboboxModel_AO), model_names[i], model_names[i]);
    }
    gtk_widget_set_name(ComboboxModel_AO, "ComboboxModel_AO");
    

    //Create attack button
    ButtonPlay_AO = gtk_button_new_with_label("Attack");
    gtk_widget_set_size_request(ButtonPlay_AO, 80, 25);
    gtk_widget_set_name(ButtonPlay_AO,"ButtonPlay_AO");


    //Create horizontal container for entry and combobox
    EntryBox_AO = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(ListBox_AO, 350, 50);

    //Creates a new animation by loading it from a file
    Animation_AO = gdk_pixbuf_animation_new_from_file("./img/it_works.gif", NULL);
    //Creates an image displaying the given animation
    ImageGif_AO = gtk_image_new_from_animation(Animation_AO);

    //Add widgets to horizontal container
    gtk_box_pack_start(GTK_BOX(EntryBox_AO), LabelID_AO, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(EntryBox_AO), EntryID_AO, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(EntryBox_AO), LabelModel_AO, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(EntryBox_AO), ComboboxModel_AO, TRUE, TRUE, 5);

    //Add horizontal conatiner to vertical container
    gtk_box_pack_start(GTK_BOX(ListBox_AO), EntryBox_AO, FALSE, FALSE, 5);

    //Add button entry to ListBox
    gtk_box_pack_start(GTK_BOX(ListBox_AO), ButtonPlay_AO, FALSE, FALSE, 5);

    gtk_box_pack_start(GTK_BOX(ListBox_AO), ImageGif_AO, FALSE, FALSE, 0);
    

    //Add listBox to layout
    gtk_layout_put(GTK_LAYOUT(Layout), ListBox_AO, 54, 100);

    //Initialize the list
    SbListInit(List_AO, ScrolledWndow_AO);
    SbListInsert(List_AO, "fb26ac5a", "Toyota", "14.000", "253.382");
    SbListInsert(List_AO, "8a58f9a2", "Citroen", "15.000", "242.792");
    SbListInsert(List_AO, "87f293", "Renault", "25.000", "202.5");

    //Get the selection associated with the list
    SelectionList_AO = gtk_tree_view_get_selection(GTK_TREE_VIEW(List_AO));
    
    g_signal_connect(SelectionList_AO, "changed", G_CALLBACK(SbListChange), NULL);
    //if(){
        handler_id = g_signal_connect(ButtonPlay_AO, "clicked", G_CALLBACK(function_ButtonAttack), NULL);
    //}else{
        //  g_signal_handler_disconnect(ButtonPlay_AO, handler_id);
    //}
    
}

void attacking_all(GtkWidget *button){
    gtk_widget_hide(ButtonPlay_AA);
    gtk_widget_show(ButtonStop_AA);
    gtk_widget_show(ImageGif_AA);
    gtk_widget_show(LabelImageGif_AA);

    enableDisasterMode();
}

void stop_attacking_all(GtkWidget *button){
    gtk_widget_hide(ButtonStop_AA);
    gtk_widget_hide(ImageGif_AA);
    gtk_widget_hide(LabelImageGif_AA);
    gtk_widget_show(ButtonPlay_AA);

    disableDisasterMode();
}

void attAllWindow(){
    LabelTitle_AA = gtk_label_new("Attack All");
    gtk_layout_put(GTK_LAYOUT(Layout), LabelTitle_AA, 160, 40);
    gtk_widget_set_size_request(LabelTitle_AA, 80, 30);
    //name for css
    gtk_widget_set_name(LabelTitle_AA,"LabelTitle_AA");


    create_list(&List_AA, &ListBox_AA, &ScrolledWndow_AA);
    gtk_widget_set_name(List_AA,"List_AA");

    //name for css
    gtk_widget_set_name(List_AA,"List_AA");

    //Creates attack button
    ButtonPlay_AA = gtk_button_new_with_label("Attack");
    gtk_widget_set_size_request(ButtonPlay_AA, 80, 25);
    gtk_widget_set_name(ButtonPlay_AA,"ButtonPlay_AA");

    //Creates attack button
    ButtonStop_AA = gtk_button_new_with_label("Stop");
    gtk_widget_set_size_request(ButtonStop_AA, 80, 25);
    gtk_widget_set_name(ButtonStop_AA,"ButtonStop_AA");
    

    LabelImageGif_AA = gtk_label_new("Attacking...");
    gtk_widget_set_size_request(LabelImageGif_AA, 50, 30);
    //name for css
    gtk_widget_set_name(LabelImageGif_AA,"LabelImageGif_AA");

    //Creates a new animation by loading it from a file
    Animation_AA = gdk_pixbuf_animation_new_from_file("./img/radar2.gif", NULL);
    //Creates an image displaying the given animation
    ImageGif_AA = gtk_image_new_from_animation(Animation_AA);

    
    //Add button attack to ListBox_AA
    gtk_box_pack_start(GTK_BOX(ListBox_AA), ButtonPlay_AA, FALSE, FALSE, 5);
    //Add button stop to ListBox_AA
    gtk_box_pack_start(GTK_BOX(ListBox_AA), ButtonStop_AA, FALSE, FALSE, 5);

    gtk_box_pack_start(GTK_BOX(ListBox_AA), ImageGif_AA, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(ListBox_AA), LabelImageGif_AA, FALSE, FALSE, 0);

    //Add ListBox_AA to layout
    gtk_layout_put(GTK_LAYOUT(Layout), ListBox_AA, 54, 80);

    //Initialize the list
    SbListInit(List_AA, ScrolledWndow_AA);

    //Remove all rows from the list
    SbListClear(List_AA);

    //Insert elements in the list
    SbListInsert(List_AA, "fb26ac5a", "Toyota", "15.000", "253.382");
    SbListInsert(List_AA, "fb26ac5b", "Toyota", "14.000", "242.792");
    SbListInsert(List_AA, "fb26ac5c", "Toyota", "14.000", "333.382");
    SbListInsert(List_AA, "8a58b6a2", "Citroen", "18.000", "242.792");
    SbListInsert(List_AA, "8a58f9a2", "Citroen", "13.000", "253.382");
    SbListInsert(List_AA, "7a58f9a1", "Citroen", "14.000", "242.792");
    SbListInsert(List_AA, "fb26ac5a", "Toyota", "15.000", "253.382");
    SbListInsert(List_AA, "fb26ac5b", "Toyota", "14.000", "242.792");
    SbListInsert(List_AA, "fb26ac5c", "Toyota", "14.000", "333.382");
    SbListInsert(List_AA, "8a58b6a2", "Citroen", "18.000", "242.792");
    SbListInsert(List_AA, "8a58f9a2", "Citroen", "13.000", "253.382");
    SbListInsert(List_AA, "7a58f9a1", "Citroen", "14.000", "242.792");
    SbListInsert(List_AA, "fb26ac5a", "Toyota", "15.000", "253.382");
    SbListInsert(List_AA, "fb26ac5b", "Toyota", "14.000", "242.792");
    SbListInsert(List_AA, "fb26ac5c", "Toyota", "14.000", "333.382");
    SbListInsert(List_AA, "8a58b6a2", "Citroen", "18.000", "242.792");
    SbListInsert(List_AA, "8a58f9a2", "Citroen", "13.000", "253.382");
    SbListInsert(List_AA, "7a58f9a1", "Citroen", "14.000", "242.792");


    g_signal_connect(ButtonPlay_AA, "clicked", G_CALLBACK(attacking_all), NULL);
    g_signal_connect(ButtonStop_AA, "clicked", G_CALLBACK(stop_attacking_all), NULL);

}

void MainWindow(){

    //Create widgets for main window and add to layout
    FrmPrincipal = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(FrmPrincipal), 458, 458);
    gtk_window_set_position(GTK_WINDOW(FrmPrincipal), GTK_WIN_POS_CENTER);
    Layout = gtk_layout_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER (FrmPrincipal), Layout);
    gtk_widget_show(Layout);

    BackgroundImage = gtk_image_new_from_file("./img/coche2.jpg");
    gtk_layout_put(GTK_LAYOUT(Layout), BackgroundImage, 0, 0);

    LabelMainTitle = gtk_label_new("ctOS-TPMS");
    gtk_layout_put(GTK_LAYOUT(Layout), LabelMainTitle, 145, 130);
    gtk_widget_set_size_request(LabelMainTitle, 80, 30);
    //name for css
    gtk_widget_set_name(LabelMainTitle,"LabelMainTitle");

    ButtonExit = gtk_button_new_with_label("Exit");
    gtk_layout_put(GTK_LAYOUT(Layout), ButtonExit, 189, 380);
    gtk_widget_set_size_request(ButtonExit, 80, 35);
    gtk_widget_set_name(ButtonExit,"ButtonExit");

    ButtonGo_AO = gtk_button_new_with_label("Attack One"); 
    gtk_layout_put(GTK_LAYOUT(Layout), ButtonGo_AO, 79, 330);
    gtk_widget_set_size_request(ButtonGo_AO, 140, 35);
    gtk_widget_set_name(ButtonGo_AO,"ButtonGo_AO");
    
    ButtonGo_AA = gtk_button_new_with_label("Attack All");
    gtk_layout_put(GTK_LAYOUT(Layout), ButtonGo_AA, 239, 330);
    gtk_widget_set_size_request(ButtonGo_AA, 140, 35);
    gtk_widget_set_name(ButtonGo_AA,"ButtonGo_AA");   

    ButtonMainWindow = gtk_button_new();
    gtk_layout_put(GTK_LAYOUT(Layout), ButtonMainWindow, 10, 10);
    gtk_widget_set_size_request(ButtonMainWindow, 30, 30);
    gtk_widget_set_name(ButtonMainWindow,"ButtonMainWindow");    

    ImageButtonBack = gtk_image_new_from_file ("./img/back_6.png");

    gtk_button_set_image (GTK_BUTTON (ButtonMainWindow), ImageButtonBack);

    attOneWindow(); 

    attAllWindow();
    
    g_signal_connect(ButtonExit, "clicked", G_CALLBACK(gturnOff), NULL);
    g_signal_connect(ButtonGo_AO, "clicked", G_CALLBACK(show_attOne_widgets), NULL);
    g_signal_connect(ButtonGo_AA, "clicked", G_CALLBACK(show_attAll_widgets), NULL);
    g_signal_connect(ButtonMainWindow, "clicked", G_CALLBACK(go_main_window), NULL);
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