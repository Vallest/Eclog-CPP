empty: "" + @""

string: "Hello" + @" World" + "!"

@"string" + "2": "Do not try and bend the spoon, that's impossible.\n" +
          "Instead, only try to realize the truth... there is no " +
          "spoon. Then you'll see that it is not the spoon that " +
          "bends, it is only yourself."

"string" + @"3": @ddd"abc"ddd + |END
    def
    END
+
    |EOF
    ghi
    EOF
+ @qqq""qqq
