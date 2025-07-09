%% Create enWelStopCause enum

classdef enWelStopCause < Simulink.IntEnumType

    enumeration
        EN_WelStop_NULL(0)
        EN_WelStop_PRM(1)
        EN_WelStop_HallFault(2)
        EN_WelStop_RelayFault(3)
        EN_WelStop_LockFault(4)
        EN_WelStop_Busoff(5)
        EN_WelStop_OtherMove(6)
        EN_WelStop_enNotGearPN(7)
        EN_WelStop_enNotLearn(8)
        EN_WelStop_enBDCDoorLost(9)
        EN_WelStop_VoltageError(10)
        EN_WelStop_LengthMoveFaild(11)
        EN_WelStop_enBWMoveSuccess(12)
        EN_WelStop_enFWMoveSuccess(13)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enWelStopCause.EN_WelStop_NULL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = 'ӭ����������ֹͣԭ��&#10;0x00: enNull Ĭ�ϳ�ʼ��״̬&#10;0x01: enIVIPrmClose �������ùر�&#10;0x02: enHallFault ��������&#10;0x03: enLockFault��ת����&#10;0x04: enRelayFault�̵�������&#10;0x05: enBusoff Busoff����&#10;0x06: enOtherMove �����ȼ������ж�&#10;0x07: enNotGearPN ��PN��&#10;0x08: enNotLearn δѧϰ&#10;0x09: enBDCDoorLost��״̬���ĵ���&#10;0x0A: enVoltageError��ѹ������&#10;0x0B: enLengthMoveFaild �����ƶ�����ʧ��&#10;0x0C: enBWMoveSuccess ���Ƴɹ�&#10;0x0D: enFWMoveSuccess ǰ�Ƴɹ�,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
