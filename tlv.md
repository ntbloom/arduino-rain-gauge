# tlv schema -- all values as uint8_t

## TLV packets sent by arduino

| DESCRIPTION      | TAG | LENGTH | VALUE                       |
| ---------------- | --- | ------ | --------------------------- |
| reserved         | 0   | n/a    | n/a                         |
| rain event       | 1   | 1      | always 1                    |
| temperature      | 2   | 4      | 32-bit float for temp, C    |
| soft reset event | 3   | 1      | always 1                    |
| hard reset event | 4   | 1      | always 1, sent after reboot |
| reserved         | 5   | n/a    | n/a                         |
| reserved         | 6   | n/a    | n/a                         |
| reserved         | 7   | n/a    | n/a                         |

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
