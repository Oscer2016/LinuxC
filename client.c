#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT    8888
#define NAME    "hepan"
#define PWD     "693640"

void make_dialog();
void init_login_widget();
void enroll(GtkWidget *widget,gpointer data);
void gtk_win_destroy(GtkWidget *widget,gpointer data);
void gtk_dialog_destroy(GtkWidget *widget, gpointer data);
void gtk_win_chat(GtkWidget *widget, gpointer data);
void chat_single(GtkWidget *widget, gpointer data);
void chat_group(GtkWidget *widget, gpointer data);
void send_file(GtkWidget *widget, gpointer data);
void modify_passwd(GtkWidget *widget, gpointer data);
void manager_entrance(GtkWidget *widget, gpointer data);
void file_ok_sel( GtkWidget *w, GtkFileSelection *fs );

struct user {
	char username[16];
	char password[17];
}info;

//将登陆窗体独立成一个结构体
struct login_widget{
        GtkWidget *window;          //主窗体
        GtkWidget *label_tips;      //用于信息提示的标签
        GtkWidget *button_login;    //两个按钮，一个点击后登录，一个点击后退出
        GtkWidget *button_enroll; 
        GtkWidget *button_cancel; 
        GtkWidget *entry_username;  //两个文本框，用于输入用户名和密码
        GtkWidget *entry_pwd;
        GtkWidget *label_username;  //两个标签用于显示username文本框和password文本框提示
        GtkWidget *label_pwd;
        GtkWidget *label_pwd2;
        GtkWidget *vbox;            //垂直布局盒子，包含以下三个水平布局盒子
        GtkWidget *hbox_username;   //包含用户名提示标签和用户名文本框，下面的HBOX作用类似
        GtkWidget *hbox_pwd;
        GtkWidget *hbox_pwd2;
        GtkWidget *hbox_button;
        GtkWidget *verify_pwd;      //确认密码
}wgt;

void make_dialog(GtkWidget *widget, gpointer window)
{
    GtkWidget *dialog;
    GtkWidget *label;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *vbox;
    GtkWidget *hbox;

    dialog = gtk_dialog_new();
    //向对话框中加入一个文本标签
    vbox = GTK_DIALOG(dialog)->vbox;
    label = gtk_label_new("确认退出?");
    gtk_box_pack_start(GTK_BOX(vbox),label,TRUE,TRUE,30);

    //向对话框中加入两个按钮
    hbox = GTK_DIALOG(dialog)->action_area;
    button1 = gtk_button_new_with_label("是");
    gtk_box_pack_start(GTK_BOX(hbox),button1,FALSE,FALSE,0);
    button2 = gtk_button_new_with_label("否");
    gtk_box_pack_start(GTK_BOX(hbox),button2,FALSE,FALSE,0);
    gtk_widget_show_all(dialog);

    g_signal_connect(G_OBJECT(button1),"clicked",G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect(G_OBJECT(button2),"clicked",G_CALLBACK(gtk_dialog_destroy),(void *)dialog);
}

void gtk_win_chat(GtkWidget *widget, gpointer data)
{
    /*
    GtkWidget *label, *toolbar;
    GtkWidget *vbox;
    GtkWidget *label2, *toolbar2;
    GtkToolItem *font, *font2;
    */
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;
    GtkWidget *button4;
    GtkWidget *button5;
    GtkWidget *button6;
    GtkWidget *window;
    GtkWidget *image1;
    GtkWidget *image2;
    GtkWidget *sep;
    GtkWidget *label;
    GtkWidget *vbox;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 600);

    gtk_window_set_title(GTK_WINDOW(window),"选择窗口");
    gtk_window_set_resizable(GTK_WINDOW(window),TRUE);
    
    vbox = gtk_vbox_new(TRUE,10);
    image1 = gtk_image_new_from_file("qq1_1.jpg");
    gtk_box_pack_start(GTK_BOX(vbox),image1,FALSE,FALSE,10);
    button1 = gtk_button_new_with_label("私聊");
    gtk_box_pack_start(GTK_BOX(vbox),button1,FALSE,FALSE,10);
    button2 = gtk_button_new_with_label("群聊");
    gtk_box_pack_start(GTK_BOX(vbox),button2,FALSE,FALSE,10);
    button3 = gtk_button_new_with_label("传文件");
    gtk_box_pack_start(GTK_BOX(vbox),button3,FALSE,FALSE,10);
    button4 = gtk_button_new_with_label("修改密码");
    gtk_box_pack_start(GTK_BOX(vbox),button4,FALSE,FALSE,10);
    button5 = gtk_button_new_with_label("管理员入口");
    gtk_box_pack_start(GTK_BOX(vbox),button5,FALSE,FALSE,10);
    sep = gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(vbox),sep,FALSE,FALSE,0);
    button6 = gtk_button_new_with_label("返回登录界面");
    gtk_box_pack_start(GTK_BOX(vbox),button6,FALSE,FALSE,10);
    label = gtk_label_new("客服: 18709261963\n邮箱: hepan@xiyoulinux.org\nCopyright©2016-?,designed by hp,All Rights Reserved");
    gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,10);
    
    //获取用户信息
    char *name;
    char *pwd;
    struct login_widget *wgt;
    wgt = (struct loging_widget *)data;
    
    //获取输入的信息
    name = gtk_entry_get_text(GTK_ENTRY(wgt->entry_username));
    pwd = gtk_entry_get_text(GTK_ENTRY(wgt->entry_pwd));
    
    //strcpy(info.username,name);
    //strcpy(info.password,pwd);
    
    if((strcmp(name,NAME) == 0) && (strcmp(pwd,PWD) == 0)) {
        gtk_container_add(GTK_CONTAINER(window),vbox);
        gtk_widget_show_all(window);
    } else {
        gtk_label_set_text(GTK_LABEL(wgt->label_tips),"用户名或密码错误");
    }

    g_signal_connect(GTK_OBJECT(window),"delete_event",GTK_SIGNAL_FUNC(make_dialog),(gpointer)window);
    g_signal_connect(GTK_OBJECT(button6),"clicked",GTK_SIGNAL_FUNC(gtk_dialog_destroy),(void *)window);
    
    g_signal_connect(GTK_OBJECT(button1),"clicked",GTK_SIGNAL_FUNC(chat_single),NULL);
    g_signal_connect(GTK_OBJECT(button2),"clicked",GTK_SIGNAL_FUNC(chat_group),NULL);
    g_signal_connect(GTK_OBJECT(button3),"clicked",GTK_SIGNAL_FUNC(send_file),NULL);
    g_signal_connect(GTK_OBJECT(button4),"clicked",GTK_SIGNAL_FUNC(modify_passwd),NULL);
    g_signal_connect(GTK_OBJECT(button5),"clicked",GTK_SIGNAL_FUNC(manager_entrance),NULL);
    
	//g_signal_connect_swapped(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit), NULL);
}

void chat_single(GtkWidget *widget, gpointer data)
{
    GtkWidget *hbox;
    GtkWidget *hbox1;
    GtkWidget *hbox2;
    GtkWidget *hbox3;
    GtkWidget *hbox4;
    GtkWidget *vbox1;
    GtkWidget *vbox2;
    GtkWidget *vbox3;
    GtkWidget *scroll_box1;
    GtkWidget *text1;
    GtkWidget *scroll_box2;
    GtkWidget *text2;
    GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *image;
    GtkWidget *button_history;
    GtkWidget *button_friend;
    GtkWidget *button_fresh;
    GtkWidget *button_send;
    GtkWidget *button_chat;
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *sep;

    sep = gtk_vseparator_new();

    wgt.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(wgt.window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(wgt.window), 500, 700);

    gtk_window_set_title(GTK_WINDOW(wgt.window),"私聊窗口");
    gtk_window_set_resizable(GTK_WINDOW(wgt.window),TRUE);

    image = gtk_image_new_from_file("qq2_1.jpg");
    button_history = gtk_button_new_with_label("历史记录");
    button_friend = gtk_button_new_with_label("好友管理");
    label1 = gtk_label_new("好友列表");
    label2 = gtk_label_new("输入聊天好友");
    entry1 = gtk_entry_new_with_max_length(147);
    gtk_widget_set_size_request(entry1,340,30);
    entry2 = gtk_entry_new_with_max_length(15);
    button_fresh = gtk_button_new_with_label("刷新");
    button_send = gtk_button_new_with_label("发送");
    button_chat = gtk_button_new_with_label("开始聊天");

    hbox = gtk_hbox_new(FALSE,0);
    vbox1 = gtk_vbox_new(FALSE,0);
    vbox2 = gtk_vbox_new(FALSE,0);
    vbox3 = gtk_vbox_new(FALSE,0);
    hbox1 = gtk_hbox_new(FALSE,0);
    hbox2 = gtk_hbox_new(FALSE,0);
    hbox3 = gtk_hbox_new(FALSE,0);
    hbox4 = gtk_hbox_new(FALSE,0);
    scroll_box1 = gtk_scrolled_window_new(NULL,NULL);
    text1 = gtk_text_view_new();
    //gtk_editable_set_editable(GTK_EDITABLE(text1),FALSE);
    scroll_box2 = gtk_scrolled_window_new(NULL,NULL);
    text2 = gtk_text_view_new();
    //gtk_editable_set_editable(GTK_EDITABLE(text2),FALSE);
    
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll_box1), GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll_box2), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scroll_box1), text1);
    gtk_container_add(GTK_CONTAINER(scroll_box2), text2);
    gtk_widget_set_size_request(scroll_box1,400,600);
    gtk_widget_set_size_request(scroll_box2,200,500);

    gtk_box_pack_start(GTK_BOX(hbox),vbox1,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(hbox),sep,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(hbox),vbox2,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(hbox1),image,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(hbox1),button_history,FALSE,FALSE,10);
    gtk_box_pack_end(GTK_BOX(hbox1),button_friend,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(hbox2),scroll_box1,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(hbox3),entry1,FALSE,FALSE,10);
    gtk_box_pack_end(GTK_BOX(hbox3),button_send,FALSE,FALSE,10);

    gtk_box_pack_start(GTK_BOX(hbox4),label1,FALSE,FALSE,10);
    gtk_box_pack_end(GTK_BOX(hbox4),button_fresh,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(vbox3),scroll_box2,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(vbox3),label2,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(vbox3),entry2,FALSE,FALSE,10);
    gtk_box_pack_end(GTK_BOX(vbox3),button_chat,FALSE,FALSE,10);

    gtk_container_add(GTK_CONTAINER(wgt.window),hbox);
    gtk_container_add(GTK_CONTAINER(vbox1),hbox1);
    gtk_container_add(GTK_CONTAINER(vbox1),hbox2);
    gtk_container_add(GTK_CONTAINER(vbox1),hbox3);
    gtk_container_add(GTK_CONTAINER(vbox2),hbox4);
    gtk_container_add(GTK_CONTAINER(vbox2),vbox3);

    gtk_widget_show_all(wgt.window);
}

void chat_group(GtkWidget *widget, gpointer data)
{
    GtkWidget *hbox;
    GtkWidget *hbox1;
    GtkWidget *hbox2;
    GtkWidget *hbox3;
    GtkWidget *vbox1;
    GtkWidget *vbox2;
    GtkWidget *scroll_box1;
    GtkWidget *text1;
    GtkWidget *scroll_box2;
    GtkWidget *text2;
    GtkWidget *entry1;
    GtkWidget *image;
    GtkWidget *button_history;
    GtkWidget *button_fresh;
    GtkWidget *button_send;
    GtkWidget *sep;

    sep = gtk_vseparator_new();

    wgt.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(wgt.window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(wgt.window), 500, 700);

    gtk_window_set_title(GTK_WINDOW(wgt.window),"群聊窗口");
    gtk_window_set_resizable(GTK_WINDOW(wgt.window),TRUE);

    image = gtk_image_new_from_file("qq2_1.png");
    button_history = gtk_button_new_with_label("历史记录");

    entry1 = gtk_entry_new_with_max_length(147);
    gtk_widget_set_size_request(entry1,340,30);
    button_fresh = gtk_button_new_with_label("刷新在线用户");
    button_send = gtk_button_new_with_label("发送");

    hbox = gtk_hbox_new(FALSE,0);
    vbox1 = gtk_vbox_new(FALSE,0);
    vbox2 = gtk_vbox_new(FALSE,0);
    hbox1 = gtk_hbox_new(FALSE,0);
    hbox2 = gtk_hbox_new(FALSE,0);
    hbox3 = gtk_hbox_new(FALSE,0);
    scroll_box1 = gtk_scrolled_window_new(NULL,NULL);
    text1 = gtk_text_view_new();
    //gtk_editable_set_editable(GTK_EDITABLE(text1),FALSE);
    scroll_box2 = gtk_scrolled_window_new(NULL,NULL);
    text2 = gtk_text_view_new();
    //gtk_editable_set_editable(GTK_EDITABLE(text2),FALSE);
    
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll_box1), GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll_box2), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scroll_box1), text1);
    gtk_container_add(GTK_CONTAINER(scroll_box2), text2);
    gtk_widget_set_size_request(scroll_box1,400,600);
    gtk_widget_set_size_request(scroll_box2,200,600);

    gtk_box_pack_start(GTK_BOX(hbox),vbox1,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(hbox),sep,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(hbox),vbox2,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(hbox1),image,FALSE,FALSE,10);
    gtk_box_pack_end(GTK_BOX(hbox1),button_history,FALSE,FALSE,10);

    gtk_box_pack_start(GTK_BOX(hbox2),scroll_box1,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(hbox3),entry1,FALSE,FALSE,10);
    gtk_box_pack_end(GTK_BOX(hbox3),button_send,FALSE,FALSE,10);

    gtk_box_pack_start(GTK_BOX(vbox2),button_fresh,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(vbox2),scroll_box2,FALSE,FALSE,10);

    gtk_container_add(GTK_CONTAINER(wgt.window),hbox);
    gtk_container_add(GTK_CONTAINER(vbox1),hbox1);
    gtk_container_add(GTK_CONTAINER(vbox1),hbox2);
    gtk_container_add(GTK_CONTAINER(vbox1),hbox3);

    gtk_widget_show_all(wgt.window);
}

void file_ok_sel( GtkWidget *w, GtkFileSelection *fs )
{
	g_print ("%s\n", gtk_file_selection_get_filename(GTK_FILE_SELECTION (fs)));
}

void send_file(GtkWidget *widget, gpointer data)
{
    GtkWidget *filew;

	//创建一个新的文件选择构件 
	filew = gtk_file_selection_new ("文件选择");
	g_signal_connect (G_OBJECT (filew), "destroy",G_CALLBACK (gtk_main_quit), NULL);
	//为 ok_button 按钮设置回调函数,连接到 file_ok_sel function 函数
	g_signal_connect (G_OBJECT (GTK_FILE_SELECTION (filew)->ok_button),"clicked",G_CALLBACK(file_ok_sel), filew);
	//为 cancel_button 设置回调函数,销毁构件
	g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(filew)->cancel_button),"clicked",G_CALLBACK (gtk_widget_destroy),filew);
	//设置文件名,比如这个一个文件保存对话框,我们给了一个缺省文件名
	
	gtk_file_selection_set_filename (GTK_FILE_SELECTION(filew),"qq1_1.jpg");
	gtk_widget_show (filew);
    //gtk_widget_destroy(filew);
    g_signal_connect(GTK_OBJECT(filew),"delete_event",GTK_SIGNAL_FUNC(make_dialog), NULL);
}

void modify_passwd(GtkWidget *widget, gpointer data)
{
    wgt.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(wgt.window), GTK_WIN_POS_CENTER);
    wgt.label_tips = gtk_label_new("修改密码");
    wgt.button_enroll = gtk_button_new_with_label("确认修改");
    wgt.button_cancel = gtk_button_new_with_label("取消修改");
   
    wgt.entry_username = gtk_entry_new_with_max_length(16);
    wgt.entry_pwd = gtk_entry_new_with_max_length(16);
    wgt.verify_pwd = gtk_entry_new_with_max_length(16);
    wgt.label_username = gtk_label_new("旧密码");
    wgt.label_pwd = gtk_label_new("新密码");
    wgt.label_pwd2 = gtk_label_new("确认密码");
    wgt.vbox = gtk_vbox_new(FALSE,20);
    wgt.hbox_username = gtk_hbox_new(FALSE,20);
    wgt.hbox_pwd = gtk_hbox_new(FALSE,20);
    wgt.hbox_pwd2 = gtk_hbox_new(FALSE,20);
    wgt.hbox_button = gtk_hbox_new(FALSE,20);

    gtk_window_set_title(GTK_WINDOW(wgt.window),"密码修改窗口");
    gtk_window_set_resizable(GTK_WINDOW(wgt.window),FALSE);

    gtk_box_pack_start(GTK_BOX(wgt.hbox_username),wgt.label_username,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_username),wgt.entry_username,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_pwd),wgt.label_pwd,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_pwd),wgt.entry_pwd,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_pwd2),wgt.label_pwd2,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_pwd2),wgt.verify_pwd,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_button),wgt.button_enroll,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_button),wgt.button_cancel,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.vbox),wgt.label_tips,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.vbox),wgt.hbox_username,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.vbox),wgt.hbox_pwd,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.vbox),wgt.hbox_pwd2,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.vbox),wgt.hbox_button,TRUE,FALSE,10);
    
    gtk_entry_set_visibility(GTK_ENTRY(wgt.entry_username),FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(wgt.entry_username),'*');
    gtk_entry_set_visibility(GTK_ENTRY(wgt.verify_pwd),FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(wgt.verify_pwd),'*');
    gtk_entry_set_visibility(GTK_ENTRY(wgt.entry_pwd),FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(wgt.entry_pwd),'*');
    g_signal_connect(G_OBJECT(wgt.button_cancel),"clicked",G_CALLBACK(gtk_dialog_destroy),(void *)wgt.window);
    
    gtk_container_add(GTK_CONTAINER(wgt.window),wgt.vbox);
    gtk_widget_show_all(wgt.window); 
}

void manager_entrance(GtkWidget *widget, gpointer data)
{
	GtkWidget *scroll_box;
	GtkWidget *text;
	GtkWidget *button1;
	GtkWidget *button2;
	GtkWidget *button3;

    wgt.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(wgt.window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(wgt.window), 400, 600);

    gtk_window_set_title(GTK_WINDOW(wgt.window),"管理窗口");
    gtk_window_set_resizable(GTK_WINDOW(wgt.window),TRUE);

    wgt.vbox = gtk_vbox_new(FALSE,20);

	scroll_box = gtk_scrolled_window_new(NULL,NULL);
    text = gtk_text_view_new();
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll_box), GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scroll_box), text);
    gtk_widget_set_size_request(scroll_box,250,400);

   	button1 = gtk_button_new_with_label("显示在线用户");
    button2 = gtk_button_new_with_label("查看聊天记录");
    button3 = gtk_button_new_with_label("踢除用户");   
    
    gtk_box_pack_start(GTK_BOX(wgt.vbox),scroll_box,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.vbox),button1,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.vbox),button2,FALSE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.vbox),button3,FALSE,FALSE,10);

    gtk_container_add(GTK_CONTAINER(wgt.window),wgt.vbox);
    gtk_widget_show_all(wgt.window);        
}

void gtk_dialog_destroy(GtkWidget *widget, gpointer data)
{
    gtk_widget_destroy((GtkWidget *)data);
}


void enroll(GtkWidget *widget,gpointer data)
{
    wgt.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(wgt.window), GTK_WIN_POS_CENTER);
    wgt.label_tips = gtk_label_new("欢迎注册");
    wgt.button_enroll = gtk_button_new_with_label("注册");
    wgt.button_cancel = gtk_button_new_with_label("取消");
   
    wgt.entry_username = gtk_entry_new_with_max_length(15);
    wgt.entry_pwd = gtk_entry_new_with_max_length(16);
    wgt.verify_pwd = gtk_entry_new_with_max_length(16);
    wgt.label_username = gtk_label_new("用户名");
    wgt.label_pwd = gtk_label_new("密码");
    wgt.label_pwd2 = gtk_label_new("确认密码");
    wgt.vbox = gtk_vbox_new(FALSE,20);
    wgt.hbox_username = gtk_hbox_new(FALSE,20);
    wgt.hbox_pwd = gtk_hbox_new(FALSE,20);
    wgt.hbox_pwd2 = gtk_hbox_new(FALSE,20);
    wgt.hbox_button = gtk_hbox_new(FALSE,20);

    gtk_window_set_title(GTK_WINDOW(wgt.window),"注册窗口");
    gtk_window_set_resizable(GTK_WINDOW(wgt.window),FALSE);

    gtk_box_pack_start(GTK_BOX(wgt.hbox_username),wgt.label_username,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_username),wgt.entry_username,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_pwd),wgt.label_pwd,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_pwd),wgt.entry_pwd,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_pwd2),wgt.label_pwd2,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_pwd2),wgt.verify_pwd,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_button),wgt.button_enroll,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_button),wgt.button_cancel,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.vbox),wgt.label_tips,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.vbox),wgt.hbox_username,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.vbox),wgt.hbox_pwd,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.vbox),wgt.hbox_pwd2,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.vbox),wgt.hbox_button,TRUE,FALSE,10);
    
    gtk_entry_set_visibility(GTK_ENTRY(wgt.verify_pwd),FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(wgt.verify_pwd),'*');
    gtk_entry_set_visibility(GTK_ENTRY(wgt.entry_pwd),FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(wgt.entry_pwd),'*');
    g_signal_connect(G_OBJECT(wgt.button_cancel),"clicked",G_CALLBACK(gtk_dialog_destroy),(void *)wgt.window);
    
    gtk_container_add(GTK_CONTAINER(wgt.window),wgt.vbox);
    gtk_widget_show_all(wgt.window);
}

void init_login_widget()
{
    GtkWidget *image;
    GtkWidget *frame;
    char *name;
    char *pwd;

    image = gtk_image_new_from_file("qq1_1.jpg");
    wgt.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(wgt.window), GTK_WIN_POS_CENTER);
    //frame = gtk_frame_new(NULL);
    //gtk_container_add(GTK_CONTAINER(frame),image);
    //gtk_container_add(GTK_CONTAINER(wgt.window),frame);
    wgt.label_tips = gtk_label_new("欢迎登录聊天室");
    wgt.button_login = gtk_button_new_with_label("登录");
    wgt.button_enroll = gtk_button_new_with_label("注册");
    wgt.entry_username = gtk_entry_new_with_max_length(15);
    wgt.entry_pwd = gtk_entry_new_with_max_length(16);
    wgt.label_username = gtk_label_new("用户名");
    wgt.label_pwd = gtk_label_new("密码");
    wgt.vbox = gtk_vbox_new(FALSE,20);
    wgt.hbox_username = gtk_hbox_new(FALSE,20);
    wgt.hbox_pwd = gtk_hbox_new(FALSE,20);
    wgt.hbox_button = gtk_hbox_new(FALSE,20);
    
    //设置窗体
    gtk_window_set_title(GTK_WINDOW(wgt.window),"登录窗口");
    gtk_window_set_resizable(GTK_WINDOW(wgt.window),FALSE);
    
    //设置布局盒子
    gtk_box_pack_start(GTK_BOX(wgt.hbox_username),wgt.label_username,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_username),wgt.entry_username,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_pwd),wgt.label_pwd,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_pwd),wgt.entry_pwd,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_button),wgt.button_login,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_button),wgt.button_enroll,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.vbox),wgt.label_tips,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.vbox),wgt.hbox_username,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.vbox),wgt.hbox_pwd,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.vbox),wgt.hbox_button,TRUE,FALSE,10);
    
    //设置密码框不可见，用户输入时显示“*”
    gtk_entry_set_visibility(GTK_ENTRY(wgt.entry_pwd),FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(wgt.entry_pwd),'*');
    
    //g_signal_connect(GTK_OBJECT(wgt.window),"delete_event",GTK_SIGNAL_FUNC(make_dialog),(gpointer)wgt.window);
    g_signal_connect(GTK_OBJECT(wgt.window),"destroy",GTK_SIGNAL_FUNC(make_dialog),NULL);
    g_signal_connect(GTK_OBJECT(wgt.button_enroll),"clicked",GTK_SIGNAL_FUNC(enroll),NULL);
    g_signal_connect(G_OBJECT(wgt.button_login),"clicked",G_CALLBACK(gtk_win_chat),&wgt);
    gtk_container_add(GTK_CONTAINER(wgt.window),wgt.vbox);
    gtk_widget_show_all(wgt.window);
}

int main(int argc,char *argv[])
{
    gtk_init(&argc,&argv);
    
    init_login_widget();
    
    gtk_main();
    
    return 0;
}
