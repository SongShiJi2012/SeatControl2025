%% Create enMemStopCause enum

classdef enMemStopCause < Simulink.IntEnumType

    enumeration
        EN_MemStop_NULL(0)
        EN_MemStop_Learn(1)
        EN_MemStop_OtherMove(2)
        EN_MemStop_HallErr(3)
        EN_MemStop_RelayErr(4)
        EN_MemStop_StallErr(5)
        EN_MemStop_NotON(6)
        EN_MemStop_NotGearPN(7)
        EN_MemStop_SpeedError(8)
        EN_MemStop_PosiError(9)
        EN_MemStop_ConfigError(10)
        EN_MemStop_NapError(11)
        EN_MemStop_MotorRunErr(12)
        EN_MemStop_EEPROMErr(13)
        EN_MemStop_VoltageErr(14)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enMemStopCause.EN_MemStop_NULL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '���书��ֹͣԭ��&#10;0����&#10;1��δѧϰ&#10;2�������˶�&#10;3����������&#10;4���̵���ճ��&#10;5����ת����&#10;6����ON��&#10;7����λ��P/N&#10;8�����ٹ���&#10;9��λ�ô���&#10;10�����书��ʧ��&#10;11��С�ģʽ��&#10;12������˶�&#10;13��e2p����&#10;14����ѹ����,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
