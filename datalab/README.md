# [Data Lab](http://csapp.cs.cmu.edu/3e/labs.html)*[Updated 11/2/18]*

> 11/2/18 新鲜出炉的 Data Lab，不同时期的 lab 内容会不一样。

## bitXor

```c
/*s
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  // 德摩根定律
  // a xor b = (~a | ~b) & (a | b)
  // = ~(a & b) & ~(~a & ~b)
  return ~(~x & ~y) & ~(x & y);
}
```

虽然这题比较简单，但我还是想了好久。主要是我把这个德摩根定律忘得差不多了，记得在离散数学里讲过。

利用的性质主要是： 

- a ^ b = (~a | ~b) & (a | b)
- (~a | ~b) = ~(a & b)

## tmin

```c
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  // minimum tow's complement is 0x80000000
  return 1 << 31;
}
```

最简单的一题，最小的有符号数是 `0x80000000`。

---

## isTmax

```c
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
    // tmax = 0x7fffffff
    return !(x ^ 0x7fffffff);
}
```

我一开始是像上面这样写的，如果没有限定的话这样是对的。但是整数部分的要求比较严格：

```
Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
```

而且这一题不能使用移位操作，就不能通过移位来得到 `0x7fffffff`。然后只能Google了。。。

这是我 Google 到的版本:

```c
int isTmax(int x) {
  // creates i = x plus 1 then makes x = that number plus x.
  // then flips the bits of x and bangs i, adds them and returns.
  // this effectively checks if the number was tmax
  // because if it was adding 1 would result in a leading 1.
  // you flips the bits to get 1 and add either 0 or 1
  // and return the opposite of that by banging x to get 1 for true or 0 for
  // flase
  int i = x + 1;
  x = x + i;
  x = ~x;
  i = !i;
  x = x + i;
  return !x;
}
```

## allOddBits

和上一题一样，我一开始也违反了这条规定：

```
Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
```

幸运的是，这题可以用移位：

```c
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  // x AND mask 0xAAAAAAAA(1010...1010), then XOR mask
  int m = 0xAA;
  m = (m << 8) | m;
  m = (m << 8) | m;
  m = (m << 8) | m;
  m = (m << 8) | m;
  return !((x & m) ^ m);
}
```

主要是利用了 `0xAAAAAAAA` 这个 mask，`x` 和 mask 相与来判断是否全部的奇数位都被置1。

## negate

```c
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  // two's complement equals ones' complement + 1
  return (~x) + 1;
}
```

一个数取反加一，就是它的负数，利用了补码的性质。

---

## isAsciiDigit

```c
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0'
 * to '9') Example: isAsciiDigit(0x35) = 1. isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  // todo flow max ops
  int _0 = x ^ 0x30;
  int _1 = x ^ 0x31;
  int _2 = x ^ 0x32;
  int _3 = x ^ 0x33;
  int _4 = x ^ 0x34;
  int _5 = x ^ 0x35;
  int _6 = x ^ 0x36;
  int _7 = x ^ 0x37;
  int _8 = x ^ 0x38;
  int _9 = x ^ 0x39;
  return !_0 | !_1 | !_2 | !_3 | !_4 | !_5 | !_6 | !_7 | !_8 | !_9;
}
```

这题我目前想到的解法就是这样，很明显超过了操作符个数的限制，而且看上去很蠢。就是判断这个数是否等于`‘0’`到`‘9’`中的一个。

## conditional

```c
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
```

在 `15213 - Recitation 3 - Datalab` 中有关于这题的小提示：

```c
//Find an algorithm for computing the expression (cond) ? t : //f, which equals t if cond is
//1 and f if cond is 0.
int conditional(int cond, int t, int f) {
/* Compute a mask that equals 0x00000000 or
0xFFFFFFFF depending on the value of cond */
int mask = ______________________________________;
/* Use the mask to toggle between returning t or returning f */
return __________________________________________;
}
```

当 x 取 0 时，返回 z，否则，返回 y。假设 `x = 0` 时，取 `mask = 0xffffffff`，否则，`mask = 0x0`。

```c
int conditional(int x, int y, int z) {
  // when x = 0, t1 is overflow, it's value is 0
  int t1 = ~x + 1;
  // when x = 0, t2 =0, else its MSB is 1
  int t2 = x | t1;
  // when x = 0, t3 = 0xffffffff, else t3's MSB is 0
  int t3 = ~t2;
  // arithmetical shift
  // x = 0, mask = 0xffffffff, else mask = 0x0
  int mask = t3 >> 31;
  // use mask to toggle between y and z
  // x = 0, return z, else return y
  return (~mask & y) | (mask & z);
}
```

## isLessOrEqual

```c
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  // Cases:
  // 1. x == y
  // 2. x, y has different sign, so the negative is less
  // if just do x -y, it may overflow when x,y has different sign.
  // 3. x - y < 0, when x,y has same sign
  int mask = 0x1;
  int equals = !(x ^ y);

  int x_sign = (x >> 31) & mask;
  int y_sign = (y >> 31) & mask;
  // sign is diff and x_sign is 1
  int diff_sign = x_sign ^ y_sign;
  int case2 = diff_sign & x_sign;

  int neg_y = (~y) + 1;
  // use logical right shift, but casting is not allowed.
  // int less =  (unsigned)(x + neg_y) >> 31;
  // less is MSB(sign bit): 0 -> x - y > 0, 1-> x - y < 0
  int less = ((x + neg_y) >> 31) & mask;
  return equals | case2 | (!diff_sign & less);
}
```

考虑返回 1 的 3 种情况：

1. x == y
2. x , y 不同号且 x 是负数
3. x, y 同号，x - y  < 0

为什么需要考虑 x, y 是否同号呢？

其实我一开始也只考虑了两种情况，即 x == y；x - y < 0。在进行测试的时候有如下输出：

```
ERROR: Test isLessOrEqual(-2147483648[0x80000000],2147483647[0x7fffffff]) failed...
...Gives 0[0x0]. Should be 1[0x1]
```

很明显 `0x80000000` 应该小于 `0x7fffffff`，但是却输出了 0。因为 `0x80000000 + 0x80000001` 发生了负溢出，产生的结果是一个大于 0 的数。所以 `less`会是 0。  

---

## logicalNeg

```c
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x) {
  // when x = 0, t1 is overflow, it's value is 0
  int t1 = ~x + 1;
  // when x = 0, t2 =0, else its MSB is 1
  int t2 = x | t1;
  // when x = 0, t3 = 0xffffffff, else t3's MSB is 0
  int t3 = ~t2;
  // logical shift
  // return (unsigned)t3 >> 31;
  // x = 0, mask = 0x1, else mask = 0x0
  return (t3 >> 31) & 1;
}
```

和 conditional 那题类似，不过我开始使用的是 `(unsigned)t3 >> 31;`，转化为 unsigned 执行逻辑右移来直接获取 MSB。但是题目是不允许使用强制类型转换的，所以改成 ` (t3 >> 31) & 1`。

## howManyBits

> //todo

---

> //todo Floating  point

## floatScale2

## floatFloat2Int

## floatPower2