%% Create enHeatStopReason enum

classdef enHeatStopReason < Simulink.IntEnumType

    enumeration
        EN_HEAT_STOP_R_NONE(0)
        EN_HEAT_STOP_R_VOL(1)
        EN_HEAT_STOP_R_FAULT(2)
        EN_HEAT_STOP_R_CMD(3)
        EN_HEAT_STOP_R_FACTORY(4)
        EN_HEAT_STOP_R_TIME(5)
        EN_HEAT_STOP_R_LOSS(6)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enHeatStopReason.EN_HEAT_STOP_R_NONE;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '���Ƚ���ԭ��&#10;0���޽���&#10;1����ѹģʽ����&#10;2�����ڹ���&#10;3������������Ч&#10;4���ָ�����&#10;5�������ʱ&#10;6�����߽���,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
