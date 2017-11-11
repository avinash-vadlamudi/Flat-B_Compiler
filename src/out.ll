; ModuleID = 'FlatB Compiler'

@c = common global [3 x i32] zeroinitializer, align 4
@i = common global i32 0, align 4
@b = common global i32 0, align 4
@a = common global i32 0, align 4
@0 = private unnamed_addr constant [3 x i8] c"%d\00"
@1 = private unnamed_addr constant [7 x i8] c"%d %d \00"

define i32 @main() {
entry:
  %0 = call i32 @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @0, i32 0, i32 0), i32* @a)
  %1 = load i32, i32* @a
  %AddOp = add i32 %1, 1
  store i32 %AddOp, i32* @b
  %2 = load i32, i32* @b
  %3 = load i32, i32* @a
  %4 = call i32 @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @1, i32 0, i32 0), i32 %2, i32 %3)
  ret i32 0
}

declare i32 @scanf(i8*, i32*)

declare i32 @printf(i8*, i32, i32)
