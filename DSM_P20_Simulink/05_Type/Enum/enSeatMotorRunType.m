%% Create enSeatMotorRunType enum

classdef enSeatMotorRunType < Simulink.IntEnumType

    enumeration
        EN_NULL(0)
        EN_HUMEnable(1)
        EN_ComfortEnable(2)
        EN_MemoryEnable(3)
        EN_ManualEnable(4)
        EN_LearnEnable(5)
        EN_ResetEnable(6)
        EN_GearEnable(7)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enSeatMotorRunType.EN_NULL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '����������ͣ�&#10;0���޶�����&#10;1��HUM��&#10;2�����ʣ�&#10;3��������ã�&#10;4���ֶ����ڣ�&#10;5��ѧϰ����,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
