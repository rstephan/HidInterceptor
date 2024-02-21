# HidInterceptor

Intercept functions calls to `hid.dll`.

## Usage

Copy the `hid.dll` next to the application you wanna investigate.
*Normaly the DLL next to the application will be picked first.*
Than all calls will be redirected to `C:\Windows\System32\hid.dll`.
In the meantime all relevant arguments and return values will be reported into
a `hid.txt` file for later inspection.

If you don't like the filename and/or location of the output. Set the environment
variable `HIDINTERCEPTOR_LOG` to what ever you like. E.g. `c:\temp\hid.txt`.
