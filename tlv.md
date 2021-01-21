# tlv schema

tag and length are `unsigned char` 

## TLV packets sent by arduino

| DESCRIPTION      | TAG | LENGTH | VALUE                | VALUE TYPE    |
| ---------------- | --- | ------ | -------------------- | ------------- |
| rain event       | 0   | 1      | 1                    | unsigned char |
| temperature      | 1   | 4      | temp, C              | int           |
| soft reset event | 2   | 1      | 1                    | unsigned char |
| hard reset event | 3   | 1      | 1, sent after reboot | unsigned char |
| reserved         | 4   | n/a    | n/a                  | n/a           |
| reserved         | 5   | n/a    | n/a                  | n/a           |
| reserved         | 6   | n/a    | n/a                  | n/a           |
| reserved         | 7   | n/a    | n/a                  | n/a           |

## TLV packets received by arduino

| DESCRIPTION | TAG | LENGTH | VALUE |
| ----------- | --- | ------ | ----- |
| reserved    | 0   | n/a    | n/a   |
| reserved    | 1   | n/a    | n/a   |
| reserved    | 2   | n/a    | n/a   |
| reserved    | 3   | n/a    | n/a   |
| reserved    | 4   | n/a    | n/a   |
| reserved    | 5   | n/a    | n/a   |
| reserved    | 6   | n/a    | n/a   |
| reserved    | 7   | n/a    | n/a   |
