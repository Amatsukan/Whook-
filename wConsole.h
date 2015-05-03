/// by ptr0x

__forceinline void WriteInConsole(const char *frmt_text, ...)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD nWritten;
    char text[1024];

    va_list pArgs;
    va_start(pArgs, frmt_text);
    vsprintf(text, frmt_text, pArgs);
    va_end(pArgs);

    WriteConsole(hConsole, text, strlen(text), &nWritten, NULL);
}

__forceinline void FixIOHandles()
{
    /* Output fix */
    int outParam = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
    FILE *stdout_stream = _fdopen(outParam, "w");

    *stdout = *stdout_stream;

    /* Input fix */
    int inParam = _open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE), _O_TEXT);
    FILE *stdin_stream = _fdopen(inParam, "r");

    *stdin = *stdin_stream;
}

__forceinline void CreateConsole()
{
    AllocConsole();
    FixIOHandles();

    /*while(TRUE)
    {
        WORD cmd;
        scanf("%x", &cmd);

        execute_command(cmd);
    }*/
}
