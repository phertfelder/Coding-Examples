/*

There are no technical comments for this
the idea was to create a calculator that would not use
eval().


Need to add negative sign for numbers
+/- button

Bugs: Allows multiple uses of decimal button
Multiple presses of operands causes issues.
Possible solutions= once clicked make operands unable to click
b. allow changing of operands.

*/
var calculateData=
{
firstNumber:"",
secondNumber:"",
operand:"",
res:"",
usedOp:0,
UsedDec:0,

setDecimal:function(UsedDec)
{
    this.UsedDec=UsedDec;

},
setUsedOp:function(UsedOp)
{
    this.usedOp=usedOp;
},
getUsedOp:function()
{
    return this.UsedOp;
},
getUsedDec:function()
{
    return this.UsedDec;
},


getFirstNumber: function()
{
    return this.firstNumber;
},
getSecondNumber: function()
{
    return this.secondNumber;
},
setFirstNumber:function(newFirst)
{
   this.firstNumber=newFirst;
},
setSecondNumber:function(newSecond)
{
    this.secondNumber=newSecond;
},
setOperand:function(operand)
{
    this.operand=operand;
},
getOperand:function()
{
    return this.operand;
},
getResult:function()
{
    return this.res;
},
setResult:function(newResult)
{
    this.res=newResult;
}

};

var oper={

Multiply :function(x,y)
{
    return parseFloat(x)*parseFloat(y);

},
Subtract : function(x,y)
{
    return parseFloat(x)-parseFloat(y);

},
Add: function(x,y)
{
    return parseFloat(x)+parseFloat(y);
},
Divide: function(x,y)
{
    return parseFloat(x)/parseFloat(y);
}



};



function getDigits()
{
const pressed = document.querySelector('.calculator-btn');
//const output = document. getElementById ("output") ;
const output = document.querySelector('.calcOutput')
pressed.addEventListener('click', event=>{
var pressID=(event.target.id);
//check output outputs button press.
//output.innerHTML=pressID;
var pressTarget=event.target;
var pressType=pressTarget.dataset.type;
var outputPress=output.textContent;
if (outputPress=='0'&& pressType=='n') 
{ 
   
   output.textContent=pressID;
   //outputPress=pressID;
}
else if(pressType=='n')
{
    output.textContent=output.textContent+pressID;
    //outputPress=outputPress+pressID;
}
else if(pressType=='.'&&calculateData.UsedDec==0)
{
    if(outputPress=='0'){
    output.textContent=pressID;
    }
    else
    {
        output.textContent=output.textContent+pressID;
    }
    calculateData.UsedDec=1;

}

/*Steps:
1. save first number to be used
2. save operand that is being used
3. clear display for new number
4. enter new numberj
5. if any operand or = is chosen output result
*/
else if(pressType=='^')
{
    if(parseFloat(output.textContent)==0)
    {    output.textContent='-';
    }
    else
    {
        output.textContent=parseFloat(output.textContent)*-1;
    }
}
else if(pressType =='o'&& calculateData.usedOp==0)//operator 
{
    calculateData.firstNumber=output.textContent;   //output.dataset.firstNumber=outputPress;
    calculateData.operand=pressID;
    calculateData.UsedOp=1;
    calculateData.UsedDec=0;

    output.textContent='0';
}
else if(pressType=='c')
{
    calculateData.secondNumber=output.textContent;
    calculate();
    output.textContent=calculateData.res;
}
else if(pressType=='e')
{
    calculateData.firstNumber=' ';
    calculateData.secondNumber=' ';
    output.textContent='0';
}
})
}

function calculate()
{
 
    
    //output.textContent=firstNumber;
    const firstNumber=calculateData.firstNumber;
    const secondNumber=calculateData.secondNumber;
    const operator= calculateData.operand;
    var res;
    if(operator=='+')
    {
        res=oper.Add(firstNumber,secondNumber);
        calculateData.res=res;

    }
    if(operator=='/')
    {
        if(secondNumber=='0')
        {
            calculateData.res="Undefined Press CLR for new Input.";
            return;
        }
        else
        {
        res=oper.Divide(firstNumber,secondNumber);
        calculateData.res=res;

        }

    }

    if(operator=='-')
    {
        res=oper.Subtract(firstNumber,secondNumber);
        calculateData.res=res;

    }

    if(operator=='*')
    {
        res=oper.Multiply(firstNumber,secondNumber);
        calculateData.res=res;

    }
    calculateData.UsedOp=1;
    calculateData.usedDec=0;
}


getDigits();