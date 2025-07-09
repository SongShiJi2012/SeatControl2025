%% Create enWelcomeRunSts enum

classdef enWelcomeRunSts < Simulink.IntEnumType

    enumeration
        EN_Wel_NULL(0)
        EN_Wel_BWMoveSuccess(1)
        EN_Wel_FWMoveSuccess(2)
        EN_Wel_BWMoveFail(3)
        EN_Wel_FWMoveFail(4)
        EN_Wel_FWBreakBW(5)
        EN_Wel_BWBreakFW(6)
        EN_Wel_BWOngoing(7)
        EN_Wel_FWOngoing(8)
        EN_Wel_Exit(9)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enWelcomeRunSts.EN_Wel_NULL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = 'ӭ����������״̬&#10;0x00: enNull Ĭ�ϳ�ʼ��״̬&#10;0x01: enBWMoveSuccess ���Ƴɹ�&#10;0x02: enFWMoveSuccess ǰ�Ƴɹ�&#10;0x03: enBWMoveFail ����ʧ��&#10;0x04: enFWMoveFail ǰ��ʧ��&#10;0x05: enFWBreakBW ���ƹ�����ִ��ǰ��&#10;0x06: enBWBreakFW ǰ�ƹ�����ִ�к���&#10;0x07: enBWOngoing ���ƹ�����&#10;0x08: enFWOngoing ǰ�ƹ�����&#10;0x09: enExit �˳�ӭ������,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
