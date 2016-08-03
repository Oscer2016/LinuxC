#include <gtk/gtk.h>

#define NAME    "hepan"
#define PWD     "693640"

void init_login_widget();
void enroll(GtkWidget *widget,gpointer data);
void login(GtkWidget *widget,gpointer data);
void gtk_win_destroy(GtkWidget *widget,gpointer data);
void make_dialog();
void gtk_dialog_destroy(GtkWidget *widget, gpointer data);
void gtk_win_chat(GtkWidget *widget, gpointer data);

//将登陆窗体独立成一个结构体
struct login_widget{
        GtkWidget *window;          //主窗体
        GtkWidget *label_tips;      //用于信息提示的标签
        GtkWidget *button_login;    //两个按钮，一个点击后登录，一个点击后退出
        GtkWidget *button_enroll; 
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

void make_dialog()
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
    wgt.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    wgt.label_tips = gtk_label_new("欢迎来到聊天室");       
    
    gtk_window_set_title(GTK_WINDOW(wgt.window),"聊天窗口");
}

void gtk_dialog_destroy(GtkWidget *widget, gpointer data)
{
    gtk_widget_destroy((GtkWidget *)data);
}

void gtk_win_destroy(GtkWidget *widget, gpointer data)
{
    make_dialog();
}

//登录验证函数，点击login按钮时调用
void login(GtkWidget *widget,gpointer data)
{
    char *name;
    char *pwd;
    struct login_widget *wgt;
    wgt = (struct loging_widget *)data;
    //获取输入的信息
    name = gtk_entry_get_text(GTK_ENTRY(wgt->entry_username));
    pwd = gtk_entry_get_text(GTK_ENTRY(wgt->entry_pwd));
    if((strcmp(name,NAME) == 0) && (strcmp(pwd,PWD) == 0)) {
        gtk_label_set_text(GTK_LABEL(wgt->label_tips),"欢迎来到聊天室");
        //g_signal_connect(G_OBJECT(wgt.button_login),"clicked",G_CALLBACK(gtk_win_chat),NULL);

    } else {
        gtk_label_set_text(GTK_LABEL(wgt->label_tips),"用户名或密码错误");
    }
}

void enroll(GtkWidget *widget,gpointer data)
{
    GtkWidget *button_enroll2;

    wgt.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    wgt.label_tips = gtk_label_new("欢迎注册");
   
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
    button_enroll2 = gtk_button_new_with_label("提交");

    gtk_window_set_title(GTK_WINDOW(wgt.window),"注册窗口");
    gtk_window_set_resizable(GTK_WINDOW(wgt.window),FALSE);

    gtk_box_pack_start(GTK_BOX(wgt.hbox_username),wgt.label_username,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_username),wgt.entry_username,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_pwd),wgt.label_pwd,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_pwd),wgt.entry_pwd,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_pwd2),wgt.label_pwd2,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.hbox_pwd2),wgt.verify_pwd,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.vbox),wgt.label_tips,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.vbox),wgt.hbox_username,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.vbox),wgt.hbox_pwd,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.vbox),wgt.hbox_pwd2,TRUE,FALSE,10);
    gtk_box_pack_start(GTK_BOX(wgt.vbox),button_enroll2,TRUE,FALSE,10);
    
    gtk_entry_set_visibility(GTK_ENTRY(wgt.verify_pwd),FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(wgt.verify_pwd),'*');
    gtk_entry_set_visibility(GTK_ENTRY(wgt.entry_pwd),FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(wgt.entry_pwd),'*');
    
    gtk_container_add(GTK_CONTAINER(wgt.window),wgt.vbox);
    gtk_widget_show_all(wgt.window);
}

void init_login_widget()
{
    GtkWidget *image;
    GtkWidget *frame;

    image = gtk_image_new_from_file("qq1.jpg");
    wgt.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
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
    //gtk_box_pack_start(GTK_BOX(wgt.hbox_username),image,TRUE,FALSE,10);
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
    g_signal_connect(GTK_OBJECT(wgt.button_login),"clicked",GTK_SIGNAL_FUNC(login),&wgt);
    g_signal_connect(GTK_OBJECT(wgt.window),"delete_event",GTK_SIGNAL_FUNC(gtk_win_destroy),NULL);
    g_signal_connect(GTK_OBJECT(wgt.button_enroll),"clicked",GTK_SIGNAL_FUNC(enroll),NULL);
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
