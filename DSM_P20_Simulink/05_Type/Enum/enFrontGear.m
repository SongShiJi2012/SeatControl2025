%% Create enFrontGear enum

classdef enFrontGear < Simulink.IntEnumType

    enumeration
        enNULL(0)
        enFrontGear_0(1)
        enFrontGear_1(2)
        enFrontGear_2(3)
        enFrontGear_3(4)
        enFrontGear_4(5)
        enFrontGear_5(6)
        enFrontGear_6(7)
        enFrontGear_7(8)
        enFrontGear_8(9)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enFrontGear.enNULL;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = 'enNULL�������е�λ����&#10;enFrontGear_0������0����&#10;enFrontGear_1������1����&#10;enFrontGear_2������2����&#10;enFrontGear_3������3����&#10;enFrontGear_4������4����&#10;enFrontGear_5������5����&#10;enFrontGear_6������6����&#10;enFrontGear_7������7����&#10;enFrontGear_8������8����,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
