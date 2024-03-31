var n = parseFloat(window.prompt("Enter the number a: "));
for(var i = 0; i < n; i++)
{
    for(var k = 0; k <= i; k++)
    {
        document.write("#");
    }
    document.write("<br>");
}