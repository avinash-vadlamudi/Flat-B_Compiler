; ModuleID = 'FlatB Compiler'

@sum = common global i32 0, align 4
@i = common global i32 0, align 4
@data = common global [100 x i32] zeroinitializer, align 4
@0 = private unnamed_addr constant [3 x i8] c"%d\00"
@1 = private unnamed_addr constant [12 x i8] c"sum :  %d \0A\00"
@2 = private unnamed_addr constant [7 x i8] c"sum : \00"
@3 = private unnamed_addr constant [10 x i8] c"i :  %d \0A\00"
@4 = private unnamed_addr constant [5 x i8] c"i : \00"

define i32 @main() {
entry:
  store i32 0, i32* @sum
  %0 = call i32 @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @0, i32 0, i32 0), i32* @i)
  br label %L1

L1:                                               ; preds = %nextBB2, %contBlock, %entry
  %1 = load i32, i32* @i
  %AddOp = add i32 %1, 1
  store i32 %AddOp, i32* @i
  %2 = load i32, i32* @sum
  %3 = load i32, i32* @i
  %AddOp1 = add i32 %2, %3
  store i32 %AddOp1, i32* @sum
  %4 = load i32, i32* @sum
  %CE = icmp eq i32 %4, 10
  %ifCond = icmp ne i1 %CE, false
  br i1 %ifCond, label %ifBlock, label %elseBlock

L3:                                               ; preds = %nextBB3, %ifBlock
  %5 = load i32, i32* @sum
  %6 = call i32 @printf(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @1, i32 0, i32 0), i32 %5)
  %7 = load i32, i32* @i
  %8 = call i32 @printf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @3, i32 0, i32 0), i32 %7)
  ret i32 0

ifBlock:                                          ; preds = %L1
  br label %L3

elseBlock:                                        ; preds = %L1
  br label %contBlock

contBlock:                                        ; preds = %elseBlock, %nextBB
  %9 = load i32, i32* @sum
  %CLT = icmp ult i32 %9, 60
  br i1 %CLT, label %L1, label %nextBB2

nextBB:                                           ; No predecessors!
  br label %contBlock

nextBB2:                                          ; preds = %contBlock
  %10 = load i32, i32* @sum
  %CLT4 = icmp ult i32 %10, 100
  br i1 %CLT4, label %L1, label %nextBB3

nextBB3:                                          ; preds = %nextBB2
  br label %L3
}

declare i32 @scanf(i8*, i32*)

declare i32 @printf(i8*, i32)
