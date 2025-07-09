%% Create enMassageLevel_IVI enum

classdef enMassageLevel_IVI < Simulink.IntEnumType

    enumeration
        EN_Inactive(0)
        EN_L1(1)
        EN_L2(2)
        EN_L3(3)
        EN_OFF(4)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enMassageLevel_IVI.EN_Inactive;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = 'IVIÇëÇóµµÎ»:&#10;0x0:Inactive&#10;0x1:Level1&#10;0x2:Level2&#10;0x3:Level3&#10;0x4:OFF,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
