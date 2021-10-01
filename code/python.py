
# \#\# Python 內建大數
# \* 可以直接用 int() 和各個運算子計算
# \* 雖然 Python 有 BigInt()，但用不到

from sys import stdin, stdout

def main():
    n = int(stdin.readline())
    for i in range(n):
        line = stdin.readline().split("/")
        # 可直接轉換成大數
        p = int(line[0])
        q = int(line[1])
        
        # 求最大公因數
        gcdNum = gcd(p, q)
                        
        stdout.write(str(gcdNum))
        stdout.write("\n")
    
main()


# \#\# 字串處理
# * string[start : end] 取 start ~ end - 1 的字串
# * string.find(string) 尋找字串位置

# \#\# 數學函式
# * round(number) 四捨五入


# \#\# 易錯事項
# * /   除法運算，結果總是返回浮點型別
# * //  取整除，結果返回捨去小數部分的整數
# * stdout.write(str(p)) 不能沒有 str()
#     * write 只能輸出字串
# * 測試時取值只能用以下程式(Spyder、Jupyter 實測)
input(string)
print(..., end = '')

# * 上傳程式時取值能用以下程式(Online Judge 實測可以 Accepted)
input(string)
print(..., end = '')
stdin.readline(...)
stdout.write(...)

# * 用 try 接受多行輸入
def main():
    # 用 try 接受多行輸入
    try:
        while(True):
            # 輸出對應的 n
            n = int(input(""))
            print(n)
    except:
        # 沒輸入內容可直接跳過
        pass

main()