# linux demo

---

## 1�����

ʹ��GCC���롣ͨ�� `main.c` �� `test_elog()` ������������־����������� `easylogger\inc\elog_cfg.h` �����첽���ģʽ��

### 1.1��ʹ�÷���

ʹ��ǰ����ǰ���úñ��뻷�������óɹ���ִ�� `make.sh` �ű����ȴ�������ɺ����� `out\EasyLoggerLinuxDemo` ���ɿ������н����

## 2���ļ����У�˵��

`easylogger\port\elog_port.c` ��ֲ�ο��ļ�

## 3����������

���Դ� `main.c` �еĲ���ע�ͣ����������¹��ܡ�

- `elog_set_output_enabled(false);` ����̬ʹ�ܻ�ʧ����־���
- `elog_set_filter_lvl(ELOG_LVL_WARN);` ����̬���ù������ȼ�
- `elog_set_filter_tag("main");` ����̬���ù��˱�ǩ
- `elog_set_filter_kw("Hello");` ����̬���ù��˹ؼ���
