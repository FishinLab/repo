print("hello world!")
sum = 0
num = 1
while num <= 100 do
    sum = sum + num
    num = num + 1
end
print("num:" , num)

sum = 0
for i = 0, 100 do
    sum = sum + 1
end
print("sum:" ,sum)

sum = 0
for i = 0, 100, 2 do
    sum = sum + 1
end
print("sum:" ,sum)

sum = 2
repeat
    sum = sum ^ 2
    print(sum)
until sum > 100

function fib(n)
    if n < 2 then return 1 end
    return fib(n - 2) + fib(n - 1)
end
