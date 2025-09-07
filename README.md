# turing machine simulator in cpp

## progress

Tape类：模拟纸带

State类：模拟状态；执行match的operation

Rule类：判断当前纸带值是否有对应目标State；执行Operation

TuringMachine类：模拟图灵机；执行循环

## TODO


解析输入（实现TuringMachineParser类）

## 输入

### 必选项：

- `alphabet`：由长度1的`string`组成的`array`
- `tapenum`：`int`
- `states`：由`string`组成的`array`
- `accept_states`：由`string`组成的`array`，所有元素须在`states`中出现过
- `reject_states`：由`string`组成的`array`，所有元素须在`states`中出现过
- `rules`：由`rule`结构组成的`array`
- `rule`结构：应当包含以下内容：
    - `state`：`string`，须在`states`中出现过
    - `tapes`：由`string`组成的`array`，所有元素须在`alphabet`中出现过，长度须等于`tapenum`
    - `opeartions`：由`operation`结构组成的`array`
    - `destination`：`string`，须在`states`中出现过
- `operation`结构：由`opr`结构组成的`array`，长度须等于`tapenum`
- `opr`结构：应当包含以下内容：
    - `op`：`string`，取值范围为`{"W", "L", "R", "+", "-"}`，分别代表图灵机的 写 左移一位 右移一位 值+1 值-1 操作
    - `ct`: 长度1的`string`

### 可选项：

- `name`：`string`（不提供时将被命名为`Turing Machine`）
- `initial_tapes`：由`string`组成的`array`（不提供时将默认由全空纸带构成）
- `blank`：长度1的`string`（不提供时默认为`_`）
- `agnostic`：长度1的`string`（不提供时默认为`@`）
- `initial_state`：`string`，须在`states`中出现过（不提供时默认为`states`第一个元素）

### 规定

- rules为空的状态，如未指定为accept或reject则默认设置为reject

