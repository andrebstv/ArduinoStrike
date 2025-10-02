#include <Mouse.h>
#include <Keyboard.h>
#include <io_init.h>

unsigned long timer1 = 0, timer2 = 0, timer3 = 0, timer4 = 0;
constexpr double TICK_64MS = 15.6;

bool is_timer_elapsed(unsigned long& timer, unsigned long interval)
{
    unsigned long current_time = millis();

    if (current_time - timer >= interval)
    {
        timer = current_time;
        return true;
    }

    return false;
}

void handle_mouse_middle_holded()
{
    if (is_timer_elapsed(timer1, 100 + random(10,25)))
    {
        Mouse.click(MOUSE_LEFT);
    }
}

void handle_space_button_holded()
{
    if (is_timer_elapsed(timer2, TICK_64MS * 39))
    {
        Mouse.move(0, 0, -1);
    }
    if (is_timer_elapsed(timer3, TICK_64MS * 8))
    {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.release(KEY_LEFT_CTRL);
    }
    if (is_timer_elapsed(timer4, TICK_64MS * 2))
    {
        Mouse.move(0, 0, -1);
    }
}

void smoothMouseMove(double x, double y, int smoothness = 1) {
    // const float steps = 2.6; // igual do pseudo-algoritmo, mas pode testar valores como 3,5,7...
    float steps = random(25, 56) / 10.0;
    double stepSizeX = x / steps;
    double stepSizeY = y / steps;
    int sleepTime = 1 * smoothness; // 1ms padrão, pode ajustar

    double currentX = 0, currentY = 0; // para corrigir arredondamento
    for (int i = 0; i < (int)steps; i++) {
        // Acumula para compensação de ponto flutuante
        currentX += stepSizeX;
        currentY += stepSizeY;

        // Move o mouse por um pequeno delta (tem que converter pra int para Mouse.move)
        Mouse.move((int)stepSizeX, (int)stepSizeY);

        // Pequena pausa, para simular movimento contínuo
        delay(sleepTime);
    }
    // Corrige qualquer "resíduo" por arredondamento
    int finalX = (int)(x - stepSizeX * ((int)steps));
    int finalY = (int)(y - stepSizeY * ((int)steps));
    if (finalX != 0 || finalY != 0) {
      Mouse.move(finalX, finalY);
    }
}

void handle_mouse_left_holded(const String& message)
{
    int index1 = message.indexOf(',');
    int index2 = message.indexOf(',', index1 + 1);

    if (index1 != -1 && index2 != -1)
    {
        double x = message.substring(0, index1).toDouble();
        double y = message.substring(index1 + 1, index2).toDouble();
        int smoothness = message.substring(index2 + 1).toInt();

        // Mouse.move(x, y); //Quadradao.
        // smoothMouseMove(x, y, smoothness); //Usar essa depois.
        smoothMouseMove(x, y, 1);
    }
}

void handle_keyboard_press_q()
{
    delay(10);
    Keyboard.write('q');
    delay(25);
    Keyboard.write('q');
}

void setup()
{
    delay(1000); //Delay de startup.
    Mouse.begin();
    Keyboard.begin();
    Serial.begin(115200);
    //while (!Serial);
    io_init();
    Serial.println(F_CPU);
}

volatile uint32_t timer_led;
volatile uint32_t timer_crouch;
bool flag = 1; //Remove to add pre crouch
#define T_LED 150
#define T_CROUCH 1000

void loop()
{
    if (Serial.available() > 0)
    {
        String message = Serial.readStringUntil('\0');
        LED = !LED;
        timer_led = 500;
        // Serial.print("DEBUG:[");
        // Serial.print(message);
        // Serial.println("]");

        if (message == "MOUSE_MIDDLE_HOLDED")
        {
            handle_mouse_middle_holded();
        }
        if (message == "HEART_BEAT")
        {
            LED = !LED;
            Serial.print('H');
        }
        else if (message == "SPACE_BUTTON_HOLDED")
        {
            handle_space_button_holded();
        }
        else if (message.startsWith("MOUSE_LEFT_HOLDED:"))
        {
            if (!flag) 
            {
                Keyboard.press(KEY_LEFT_CTRL);
                flag = 1;
                timer_crouch = millis();
            }
            handle_mouse_left_holded(message.substring(18));
        }
        else if (message == "MOUSE_LEFT_CLICK")
        {
            Mouse.click(MOUSE_LEFT);
            //flag = 0;
        }
        else if (message == "KEYBOARD_PRESS_Q")
        {
            handle_keyboard_press_q();
        }
        else if (message == "DESCE_100") 
        {
            // delay(3000);
            uint32_t tmove = millis();
            while ((millis() - tmove) < 3000);
            Mouse.move(0,100);
        }
        else if (message == "F_CPU_IMPRIMA") 
        {   
            Serial.print("FREQUENCIA>");
            Serial.println(F_CPU);
        }
    }
    else
    {
        if ((millis() - timer_led) > T_LED)
        {
            LED = 0;
            timer_led = millis();
        }
    }
    if ((millis() - timer_crouch) > T_CROUCH)
    {
        Keyboard.release(KEY_LEFT_CTRL);
    } 
}