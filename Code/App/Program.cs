/*
This app will have a GUI and also be responsable for flashing the boards.
The GUI will allow users to add keymaps and modify them.
This software will be modular meaning different keyboards that use the 
    mbed platform will be able to use this on their own keyboard.
Implementation order:
    keymap -> code
    create GUI to display keys and what they do
    make it possible to add your own keyboard design to the program
Future plans:
    add the ablity to create custom parts to the software to manage other things(plug-ins)(screen on keyboard etc)
*/
namespace App;

using System.Numerics;
using System.Text;
using System.Text.Json;
using Microsoft.VisualBasic;

class Program
{
    static void Main(string[] args)
    {
        KeyMap keyMap = new KeyMap();
        keyMap.Run("main_keymap.json");
    }
    
}


class KeyMap
{

        private static ReadOnlySpan<byte> Utf8Bom => new byte[] { 0xEF, 0xBB, 0xBF };
        public List<byte[]> keycodes = new List<byte[]>();

        public void Run(string fileName/*, Vector2<int,int> matrixSize*/)
    {
        ReadOnlySpan<byte> jsonReadOnlySpan = File.ReadAllBytes(fileName);

        if (jsonReadOnlySpan.StartsWith(Utf8Bom))
        {
            jsonReadOnlySpan = jsonReadOnlySpan.Slice(Utf8Bom.Length);
        }

        var reader = new Utf8JsonReader(jsonReadOnlySpan);

        while (reader.Read())
        {
            JsonTokenType jsonTokenType = reader.TokenType;
            switch (jsonTokenType)
            {
                case JsonTokenType.StartObject:
                    reader.Read();
                    Console.WriteLine("this is a startObject of value");
                    break;
                case JsonTokenType.PropertyName:
                    reader.Read();
                    Console.WriteLine("this is a propertyName of value: " + reader.GetString());
                    break;
            }
            var temp = ""; //hex from file

            // byte bytes = new byte[2];
            // bytes[0] = Convert.ToByte(hex.Substring(0, 2), 16);
            // bytes[1] = Convert.ToByte(hex.Substring(2, 2), 16);

            // keycodes.Add(bytes);

        }


    }
}