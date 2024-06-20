#ifndef GTKMM_EXAMPLE_RANGEWIDGETS_H
#define GTKMM_EXAMPLE_RANGEWIDGETS_H

#include <gtkmm.h>
#include "COpenGL.h"

class ExampleWindow : public Gtk::Window
{
public:
    ExampleWindow();
    ~ExampleWindow() override;

protected:
    //Signal handlers:
    void on_X_value_changed();
    void on_Y_value_changed();
    void on_Z_value_changed();
    void on_Yaw_value_changed();
    void on_Pitch_value_changed();
    void on_button_quit();

    //Child widgets:
    Gtk::Box m_VBox_Top;
    Gtk::Box m_VBox2;

    Gtk::Box m_HBox_XVal;
    Gtk::Box m_HBox_YVal;
    Gtk::Box m_HBox_ZVal;
    Gtk::Box m_HBox_Yaw;
    Gtk::Box m_HBox_Pitch;

    Glib::RefPtr<Gtk::Adjustment> m_adjustment_XVal;
    Glib::RefPtr<Gtk::Adjustment> m_adjustment_YVal;
    Glib::RefPtr<Gtk::Adjustment> m_adjustment_ZVal;
    Glib::RefPtr<Gtk::Adjustment> m_adjustment_Yaw;
    Glib::RefPtr<Gtk::Adjustment> m_adjustment_Pitch;

    Gtk::Scale m_Scale_XVal;
    Gtk::Scale m_Scale_YVal;
    Gtk::Scale m_Scale_ZVal;
    Gtk::Scale m_Scale_Yaw;
    Gtk::Scale m_Scale_Pitch;

    Gtk::Separator m_Separator;

    Gtk::Button m_Button_Quit;

    ////////////////////////////////////////////////////
    // OpenGL
    COpenGL m_GLArea;
};

#endif //GTKMM_EXAMPLE_RANGEWIDGETS_H
