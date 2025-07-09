%% Create enMassageMode_DSM enum

classdef enMassageMode_DSM < Simulink.IntEnumType

    enumeration
        EN_M1(0)
        EN_M2(1)
        EN_M3(2)
        EN_M4(3)
        EN_M5(4)
        EN_M6(5)
        EN_M7(6)
        EN_M8(7)
        EN_MError(8)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enMassageMode_DSM.EN_M1;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = 'DSM����ģʽ/��Ħģ�鷴��ģʽ:&#10;0x0:Mode1ȫ�����&#10;0x1:Mode2ȫ����&#10;0x2:Mode3�粿����&#10;0x3:Mode4�粿����&#10;0x4:Mode5��������&#10;0x5:Mode6��������&#10;0x6:Mode7��������&#10;0x7:Mode8��������&#10;0x8:����ģʽ,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
