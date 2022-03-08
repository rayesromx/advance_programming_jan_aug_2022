#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
/// <summary>
/// Prototipo de la funcion WinProc o Window Procedure.
/// Cuando el programa inicia, este registra informacion sobre el comportamiento de la ventana de la aplicacion.
/// Uno de los elementos mas importantes es la direccion de una funcion, llamada WindowProc en este ejemplo.
/// Esta funcion define el comportamiento de la ventana: su apariencia, como interactua el usuario, entre otras.
/// </summary>
/// <param name="hwnd"></param>
/// <param name="uMsg"></param>
/// <param name="wParam"></param>
/// <param name="lParam"></param>
/// <returns></returns>
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/// <summary>
/// Cada programa tiene un punto de entrada, en el caso de las aplicaciones de consola es el main.
/// Para el caso de aplicaciones en WinAPI, la funcion main se puede llamar wWinMain o WinMai
/// </summary>
/// <param name="hInstance">En ingles es handle to a Instance, o un manejador a una instancia (proceso en WinOS). El sistema operativo
/// usa este valor para identificar el ejecutable (.exe) cuando es cargado en memoria. Se utiliza para varias funcionalidades, por ejemplo
/// cargar bitmaps o iconos, por mencionar una.</param>
/// <param name="hPrevInstance">Este parametro ya no se utiliza. Era de utilidad en las epocas de windows de 16 bits, ahora siempre tiene un valor de cero.</param>
/// <param name="pCmdLine">Contiene los argumentos de linea de comandos como una cadena UNICODE</param>
/// <param name="nCmdShow">Es una bandera que le indica a la ventana principal de la aplicacion estara maximizada, minimizada o de tamaño normal.</param>
/// <returns>Retorna un entero que es ignorado por el SO pero se puede definir a conveniencia para algun otro programa desarrollado</returns>
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // WINAPI es una convencion, una convencion de llamada. Una convencion define como va a recibir los parametros una funcion desde donde se llame.
    
    //WinMain y wWinMain son identicos con la excepcion que los argumentos de linea de comandos se reciben con formato ANSI (WinMain)

    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    /*
    Cada ventana debe estar asociada a una Window class que no es mas que una estructura usada internamente por el sistema operativo. 
    Las Windows classes son registradas con el sistema en tiempo de ejecucion. 
    La estructura WNDCLASS tiene otros miembros que pueden ser establecidos a 0, para mas información pueden consultar la siguiente liga
    https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassa
    */
    WNDCLASS wc = { };

    //lpfnWndProc es un puntero a una funcion definida de la aplicacion llamada window procedure, "window proc" o procedimiento de ventana. 
    //Este define casi todo el comportamiento de la ventana
    wc.lpfnWndProc = WindowProc;
    //es el manejador de la instancia de la aplicacion. Se le asigna el parametro hInstance que se recibe en wWinMain
    wc.hInstance = hInstance;
    //Es una cadena que identifica la window class
    wc.lpszClassName = CLASS_NAME;

    //una vez llenada la estructura Window class, se le pasa la direccion de esta a la funcion RegisterClass la cual registre 
    //la clase de la ventana con el sistema operativo
    RegisterClass(&wc);

    //Para crear una neuva instancia de una ventana, se llama a la funcion CreateWindowEx.
    //esta funcion retorna un manejador de la nueva ventana, o retorna NULL si la creacion de la ventana falla
    HWND hwnd = CreateWindowEx(
        0,                              // este parametro permite establecer algunos comportamientos opcionales para la ventana (por ejemplo, ventanas transparentes). 
                                        // Si se manda un 0 entonces se establecen los comportamientos default
        CLASS_NAME,                     // es el nombre de la clase de la ventana
        L"Learn to Program Windows",    // El texto que se desplegara en la barra de titulo
        WS_OVERLAPPEDWINDOW,            // Este parametro define el estilo de la ventana a traves de una serie de banderas.
                                        // Estas banderas le dan a la ventana la barra de titulo, el borde, el menu del sistema, y los botones de maximizar y minimizar
        // Las siguiente 4 banderas definen la posicion y el tamaño de la ventana, usamos la constante CW_USEDEFAULT para decirle que use los valores default
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,       // este parametro sirve para establecer la ventana padre, o la ventana dueña de la nueva ventana. Establezca el padre si estas creando una ventana hijo
                    // Para una ventana de primer nivel se establece un NULL
        NULL,       // Define el menu de la ventana. Si no se tiene un menu entonces se establece NULL
        hInstance,  // Aqui se establece el manejador de la instancia
        NULL        // Se puede asignar un puntero void a datos arbitrarios. Se puede usar este valor para pasar una estrutura de datos al window procedure
    );

    //validamos que se haya creado exitosamente la ventana
    if (hwnd == NULL)
    {
        return 0;
    }

    //Para hacer la ventana visible llamamos a la siguiente funcion, donde el primer parametro es el manejador de la ventana recien creada
    //y el segundo parametro puede ser usado para minimizar o maximizar la pantalla
    ShowWindow(hwnd, nCmdShow);

    /* 
    MENSAJES DE PANTALLA

    Una aplicacion con una interfaz grafica debe responder a eventos tanto del usuario como clics, teclas presionadas, como del sistema operativo por ejemplo
    un nuevo dispositivo conectado, o Windows entrando a modo de bajo consumo.
    Estos eventos pueden ocurrir en cualquier momento y en cualquier orden por lo que, para resolver el problema de como antender estos eventos, 
    Windows una un modelo de paso de mensajes.
    Un mensaje es un codigo numerico que define un evento en particular, por ejemplo si el usuario presiona el boton izquierdo el mensaje es
    #define WM_LBUTTONDOWN    0x0201
    Algunos mensajes tiene datos asociados a ellos, por ejemplo, el clic tiene las coordenadas X,Y del cursor.

    Para pasar el mensaje a la ventana, el sistema operativo llama a la funcion WindowProc registrada para dicha ventana

    MESSAGE LOOP

    Una aplicacion recibirá miles de mensajes mientras corre (considerando que un teclazo o un clic del mouse genera un mensaje). Entonces la aplicacion necesita
    un ciclo para obtener los mensajes y despacharlos a las ventanas correctas

    Para cada hilo que crea una ventana, el sistema operativo crea una cola de mensajes. No podemos manipular directamente la cola pero si podemos extraer mensajes de ella
    usando la funcion GetMessage
    
    */

    MSG msg = { };
    /*
    GetMessage(
        &msg,   // el primer parametro es la direccion de una estructura MSG donde se guardara el mensaje recibido de la cola
        NULL,   // Los otros tres parametros te permiten filtara que mensajes extraer de la cola pero en la mayoria de los casos
        0,      // estableceremos los parametros a cero
        0       //
    )

    */
    while (GetMessage(&msg, NULL, 0, 0))
    {
        // Aunque MSG contiene la informacion del mensaje o evento como tal, nunca lo manipulamos directamente. En vez de eso, lo pasamos directoa otras dos funciones
    
        // Esta funcion esta relacionada con la entrada por teclado. Traduce los teclazos en caracteres. No es importante entenderla solo saber que se debe
        // llamar antes que la funcion DispatchMessage
        TranslateMessage(&msg);

        // Esta funcion le dice al sistema operativo que llame a la funcion Window Proc de la ventana que es el objetivo del mensaje.
        DispatchMessage(&msg);

        /*
        Supongamos que el usuario presiona un boton. Esto causa una cadena de eventos:
            1. El SO pone un mensaje WM_LBUTTONDOWN en la cola
            2. Tu programa llama a la funcion GetMessage
            3. GetMessage extrae el mensaje WM_LBUTTONDOWN de la cola y lo pone en la estructura MSG
            4. Tu programa llama a las funciones TranslateMessage y DispatchMessage
            5. Dentro de DispatchMessage, el SO llama a tu Window Proc
            6. Tu Window Proc o reacciona al mensaje o lo ignora

        Normalmente la funcion GetMessage retorna un valor diferente de cero, por lo que el ciclo pareceria nunca terminar.
        Cuando quieres salirte de la aplicacion y salirte del ciclo de mensajes, debes llamar a la funcion PostQuitMessage
             PostQuitMessage(0);
        Esta funcion pone un mensaje WM_QUIT en la cola. Este mensaje causa que GetMessage retorne cero.
        */
    }

    //retornamos un entero que para el SO no es de importancia
    return 0;
}

/// <summary>
/// La funcion WindowProc es llamada internamente por la funcion DispatchMessage.
/// LRESULT es un valor entero que el programa retorna a Windows, contiene la respuesta de tu programa a un mensaje en particular y el significado de este valor depende del codigo del mensaje.
/// CALLBACK es una convencion de llamada.  Una convencion define como va a recibir los parametros una funcion desde donde se llame.
/// La funcion WindowProc generalmente es una bloque switch que maneja todos los codigos de mensaje.
/// </summary>
/// <param name="hwnd">Manejador de la ventana</param>
/// <param name="uMsg">Codigo del mensaje o del evento</param>
/// <param name="wParam">Contiene datos adicionales al mensaje. El contenido exacto depende el codigo del mensaje. Ir a MSDN</param>
/// <param name="lParam">Contiene datos adicionales al mensaje. El contenido exacto depende el codigo del mensaje. Ir a MSDN</param>
/// <returns></returns>
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);



        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hwnd, &ps);
    }
    return 0;

    }
    //si no tenemos que manejar un mensaje en particular podemos simplemente pasar los parametros directamente a la siguiente funcion,
    //la cual ejecuta acciones default dependiendo del mensaje
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}