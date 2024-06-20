#include <epoxy/gl.h>
#include "examplewindow.h"

ExampleWindow::ExampleWindow()
:
  m_VBox_Top(Gtk::Orientation::VERTICAL, 0),
  m_VBox2(Gtk::Orientation::VERTICAL, 20),
  m_HBox_XVal(Gtk::Orientation::HORIZONTAL, 10),
  m_HBox_YVal(Gtk::Orientation::HORIZONTAL, 10),
  m_HBox_ZVal(Gtk::Orientation::HORIZONTAL, 10),
  m_HBox_Yaw(Gtk::Orientation::HORIZONTAL, 10),
  m_HBox_Pitch(Gtk::Orientation::HORIZONTAL, 10),

  m_adjustment_XVal(Gtk::Adjustment::create(0.0, 0.0, 360.0, 1.0, 2.0)),
  m_adjustment_YVal(Gtk::Adjustment::create(0.0, 0.0, 360.0, 1.0, 2.0)),
  m_adjustment_ZVal(Gtk::Adjustment::create(70.0, 0.0, 360.0, 1.0, 2.0)),
  m_adjustment_Yaw(Gtk::Adjustment::create(270.0, 0.0, 360.0, 1.0, 2.0)),
  m_adjustment_Pitch(Gtk::Adjustment::create(0.0, -89.0, 89.0, 1.0, 2.0)),

  m_Scale_XVal(m_adjustment_XVal),
  m_Scale_YVal(m_adjustment_YVal),
  m_Scale_ZVal(m_adjustment_ZVal),
  m_Scale_Yaw(m_adjustment_Yaw),
  m_Scale_Pitch(m_adjustment_Pitch),

  m_Button_Quit("Quit")
{
    g_print("[Start]\r\n");

    set_title("Example app");
    set_default_size(300, 350);

    /////////////////////////////////////////////////////

    m_GLArea.set_size_request(SCR_WIDTH, SCR_HEIGHT);

    /////////////////////////////////////////////////////

    set_child(m_VBox_Top);
    m_VBox_Top.append(m_VBox2);
    m_VBox2.append(m_GLArea);
    m_VBox2.set_expand(true);
    m_VBox2.set_margin(5);

    // X Value:
    m_HBox_XVal.append(*Gtk::make_managed<Gtk::Label>("X Pos:", 0));
    m_Scale_XVal.set_digits(1);
    m_Scale_XVal.set_value_pos(Gtk::PositionType::RIGHT);
    m_Scale_XVal.set_draw_value();
    m_Scale_XVal.set_expand(true);
    m_adjustment_XVal->signal_value_changed().connect(sigc::mem_fun(*this, &ExampleWindow::on_X_value_changed));
    m_HBox_XVal.append(m_Scale_XVal);

    // Y Value:
    m_HBox_YVal.append(*Gtk::make_managed<Gtk::Label>("Y Pos:", 0));
    m_Scale_YVal.set_digits(1);
    m_Scale_YVal.set_value_pos(Gtk::PositionType::RIGHT);
    m_Scale_YVal.set_draw_value();
    m_Scale_YVal.set_expand(true);
    m_adjustment_YVal->signal_value_changed().connect(sigc::mem_fun(*this, &ExampleWindow::on_Y_value_changed));
    m_HBox_YVal.append(m_Scale_YVal);

    // Z Value:
    m_HBox_ZVal.append(*Gtk::make_managed<Gtk::Label>("Z Pos:", 0));
    m_Scale_ZVal.set_digits(1);
    m_Scale_ZVal.set_value_pos(Gtk::PositionType::RIGHT);
    m_Scale_ZVal.set_draw_value();
    m_Scale_ZVal.set_expand(true);
    m_adjustment_ZVal->signal_value_changed().connect(sigc::mem_fun(*this, &ExampleWindow::on_Z_value_changed));
    m_HBox_ZVal.append(m_Scale_ZVal);

    // Yaw Value:
    m_HBox_Yaw.append(*Gtk::make_managed<Gtk::Label>("Yaw:", 0));
    m_Scale_Yaw.set_digits(1);
    m_Scale_Yaw.set_value_pos(Gtk::PositionType::RIGHT);
    m_Scale_Yaw.set_draw_value();
    m_Scale_Yaw.set_expand(true);
    m_adjustment_Yaw->signal_value_changed().connect(sigc::mem_fun(*this, &ExampleWindow::on_Yaw_value_changed));
    m_HBox_Yaw.append(m_Scale_Yaw);

    // Pitch Value:
    m_HBox_Pitch.append(*Gtk::make_managed<Gtk::Label>("Pitch:", 0));
    m_Scale_Pitch.set_digits(1);
    m_Scale_Pitch.set_value_pos(Gtk::PositionType::RIGHT);
    m_Scale_Pitch.set_draw_value();
    m_Scale_Pitch.set_expand(true);
    m_adjustment_Pitch->signal_value_changed().connect(sigc::mem_fun(*this, &ExampleWindow::on_Pitch_value_changed));
    m_HBox_Pitch.append(m_Scale_Pitch);

    // ---------------------------------

    m_VBox2.append(m_HBox_XVal);
    m_VBox2.append(m_HBox_YVal);
    m_VBox2.append(m_HBox_ZVal);
    m_VBox2.append(m_HBox_Yaw);
    m_VBox2.append(m_HBox_Pitch);
    m_VBox_Top.append(m_Separator);
    m_VBox_Top.append(m_Button_Quit);

    set_default_widget(m_Button_Quit);
    m_Button_Quit.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_quit));
    m_Button_Quit.set_margin(10);

    // ---------------------------------

    // Copy the initial values from GTKmm to OpenGL
    m_GLArea.m_RotationAngles[X_AXIS] = m_adjustment_XVal->get_value();
    m_GLArea.m_RotationAngles[Y_AXIS] = m_adjustment_YVal->get_value();
    m_GLArea.m_RotationAngles[Z_AXIS] = m_adjustment_ZVal->get_value();
    m_GLArea.m_RotationAngles[YAW]    = m_adjustment_Yaw->get_value();
    m_GLArea.m_RotationAngles[PITCH]  = m_adjustment_Pitch->get_value();

    m_GLArea.show();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_X_value_changed()
{
    m_GLArea.m_RotationAngles[X_AXIS] = m_adjustment_XVal->get_value();
    m_GLArea.queue_draw();
}

void ExampleWindow::on_Y_value_changed()
{
    m_GLArea.m_RotationAngles[Y_AXIS] = m_adjustment_YVal->get_value();
    m_GLArea.queue_draw();
}

void ExampleWindow::on_Z_value_changed()
{
    m_GLArea.m_RotationAngles[Z_AXIS] = m_adjustment_ZVal->get_value();
    m_GLArea.queue_draw();
}

void ExampleWindow::on_Yaw_value_changed()
{
    m_GLArea.m_RotationAngles[YAW] = m_adjustment_Yaw->get_value();
    m_GLArea.queue_draw();
}

void ExampleWindow::on_Pitch_value_changed()
{
    m_GLArea.m_RotationAngles[PITCH] = m_adjustment_Pitch->get_value();
    m_GLArea.queue_draw();
}

void ExampleWindow::on_button_quit()
{
    g_print("--- Quit ---\r\n");

    set_visible(false);
}

