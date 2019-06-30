# Disarium-Numbers
C program searching all Disarium Numbers

Disarium Number is a number in which the sum of the digits to the power of their respective position is equal to the number itself.
For example, 135 = 1^1 + 3^2 + 5^3.


Fortunately， there is a upper limit for possible disarium, that's:

99 999 999 999 999 999 999 999 (biggest number with 23 digits)
 9 970 805 384 609 063 732 919 (disarium form of the biggest 23 digits "9")
10 000 000 000 000 000 000 000 (smallest number with 23 digits)
 
 You see that the biggest disarium form of 23 digits number has only 22 digits, impossible to meet the basic requirement.
 
 
 For 22 digits number:
 
 9 999 999 999 999 999 999 999 (biggest number with 22 digits)
 1 107 867 264 956 562 636 990 (disarium form of the biggest 22 digits "9")
 1 000 000 000 000 000 000 000 (smallest number with 22 digits)
 
 From this simple check, we can know that all possible disarium number will smaller than 22 digits "9 999 999 999 999 999 999 999" (acturally smaller than its' disarium form "1 107 867 264 956 562 636 990").
 
 
 Above is the basic idea to find the possible disarium numbers: narrow down the possible limits for disarium numbers at any given number of digits.
 
 Let's go further, estimate the limtis from low bit digit end, in this way the possible limits will be greatlly narrow down when we get more digit known from low bit end. That's the core idea here shown in this program.
 
 Take an example of 3 digits number end of 5 (disarium form number is listed in braket):
 
 xx5 <= 995  (215), pass to 2nd digit
 
 x05 <= 905  (134), pass to 3rd digit
 105 <= 105 <(126), failed to next 3rd digit
 205 <= 205 >(127), fieled to next 2nd digit
 
 x15 <= 915  (135), pass to 3rd digit
 115 <= 115 <(127), failed to next 3rd digit
 215 <= 215 >(128), failed to next 2nd digit
 
 x25 <= 925  (138), pass to 3rd digit
 125 <= 125 <(130), failed to next 3rd digit
 225 <= 225 >(131), failed to next 2nd digit
 
 x35 <= 935  (143), pass to 3rd digit
 135 <= 135 =(135), pass to next 3rd digit, 135 is found as an disarium number
 235 <= 235 >(136), failed to next 2nd digit
 
 This simple example shows the idea to narrow down the possible limit for disraium numbers. A lot of other ideas for this purpose is also shown in the code, have a look and welcome for issues.
 
