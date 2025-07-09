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
            desc = 'enNULL£¨ÎÞÍÈÍÐµµÎ»ÇëÇó£©&#10;enFrontGear_0£¨ÍÈÍÐ0µµ£©&#10;enFrontGear_1£¨ÍÈÍÐ1µµ£©&#10;enFrontGear_2£¨ÍÈÍÐ2µµ£©&#10;enFrontGear_3£¨ÍÈÍÐ3µµ£©&#10;enFrontGear_4£¨ÍÈÍÐ4µµ£©&#10;enFrontGear_5£¨ÍÈÍÐ5µµ£©&#10;enFrontGear_6£¨ÍÈÍÐ6µµ£©&#10;enFrontGear_7£¨ÍÈÍÐ7µµ£©&#10;enFrontGear_8£¨ÍÈÍÐ8µµ£©,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
